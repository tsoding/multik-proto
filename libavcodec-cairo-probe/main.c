#include <stdio.h>

#include <cairo.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>

static void encode(AVCodecContext *context, AVFrame *frame,
                   AVPacket *pkt, FILE *outfile)
{
    if (frame) {
        printf("Send frame %3"PRId64"\n", frame->pts);
    }

    int ret = avcodec_send_frame(context, frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending a frame for encoding: %s\n",
                av_err2str(ret));
        exit(EXIT_FAILURE);
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(context, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return;
        } else if (ret < 0) {
            fprintf(stderr, "Error during encoding\n");
            exit(EXIT_FAILURE);
        }

        printf("Write packet %3"PRId64" (size=%5d)\n",
               pkt->pts, pkt->size);
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <output-file> <codec-name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    const char *codec_name = argv[2];

    const AVCodec *codec = avcodec_find_encoder_by_name(codec_name);
    if (codec == NULL) {
        fprintf(stderr, "Codec '%s' not found\n", codec_name);
        exit(EXIT_FAILURE);
    }

    AVCodecContext *context = avcodec_alloc_context3(codec);
    if (context == NULL) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(EXIT_FAILURE);
    }
    context->bit_rate = 400 * 1000;
    context->width = 352;
    context->height = 288;
    context->time_base = (AVRational){1, 25};
    context->framerate = (AVRational){25, 1};
    context->gop_size = 10;
    context->max_b_frames = 1;
    context->pix_fmt = AV_PIX_FMT_YUV420P;

    AVPacket *pkt = av_packet_alloc();
    if (!pkt) {
        fprintf(stderr, "Could not allocate AVPacket\n");
        exit(EXIT_FAILURE);
    }

    if (codec->id == AV_CODEC_ID_H264) {
        av_opt_set(context->priv_data, "preset", "slow", 0);
    }

    int ret = avcodec_open2(context, codec, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    AVFrame *frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(EXIT_FAILURE);
    }
    frame->format = context->pix_fmt;
    frame->width  = context->width;
    frame->height = context->height;

    ret = av_frame_get_buffer(frame, 32);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate the video frame data: %s\n",
                av_err2str(ret));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 25; i++) {
        ret = av_frame_make_writable(frame);
        if (ret < 0) {
            fprintf(stderr, "%s\n", av_err2str(ret));
            exit(EXIT_FAILURE);
        }

        for (int y = 0; y < context->height; ++y) {
            for (int x = 0; x < context->width; ++x) {
                frame->data[0][y * frame->linesize[0] + x] = x + y + i * 3;
            }
        }

        for (int y = 0; y < context->height / 2; ++y) {
            for (int x = 0; x < context->width / 2; ++x) {
                frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
                frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
            }
        }

        frame->pts = i;

        encode(context, frame, pkt, f);
    }
    encode(context, NULL, pkt, f);

    uint8_t endcode[] = {0, 0, 1, 0xb7};
    fwrite(endcode, 1, sizeof(endcode), f);

    fclose(f);
    avcodec_free_context(&context);
    av_frame_free(&frame);
    av_packet_free(&pkt);

    return EXIT_SUCCESS;
}
