#include <stdio.h>

#include <cairo.h>
#include <libavcodec/avcodec.h>

int main(int argc, char *argv[])
{
    AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        return -1;
    }

    AVCodecContext *c = avcodec_alloc_context();

    return 0;
}
