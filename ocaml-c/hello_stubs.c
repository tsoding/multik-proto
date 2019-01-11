#include <stdio.h>
#include <stdbool.h>
#include <caml/mlvalues.h>
#include <cairo.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

CAMLprim value
caml_print_hello(value unit)
{
    SDL_Rect screen_rect = {
        .x = 0, .y = 0,
        .w = SCREEN_WIDTH,
        .h = SCREEN_HEIGHT
    };

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *const window = SDL_CreateWindow(
        "Multik",
        100, 100,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *const renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH, SCREEN_HEIGHT);

    float a = 0.0f;
    bool stop = false;
    SDL_Event event;
    /* TODO: FPS is not shown */
    while (!stop) {
        while (!stop && SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                stop = true;
                break;
            }
        }

        SDL_RenderClear(renderer);

        void *pixels;
        int pitch;

        SDL_LockTexture(texture, NULL, &pixels, &pitch);

        cairo_surface_t *surface =
            cairo_image_surface_create_for_data(
                pixels,
                CAIRO_FORMAT_ARGB32,
                SCREEN_WIDTH, SCREEN_HEIGHT, pitch);
        cairo_t *cr = cairo_create(surface);

        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_paint (cr);

        cairo_select_font_face(
            cr, "serif",
            CAIRO_FONT_SLANT_NORMAL,
            CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 32.0);
        cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
        cairo_move_to(cr, 10.0, 50.0);
        cairo_show_text(cr, "4HEad");

        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
        cairo_move_to(cr, 0.0, 0.0);
        cairo_curve_to(cr, 0.0 + a, SCREEN_HEIGHT + a,
                       SCREEN_WIDTH - a, SCREEN_HEIGHT - a,
                       SCREEN_WIDTH, 0.0);
        cairo_set_line_width(cr, 5);
        cairo_stroke(cr);

        cairo_destroy(cr);
        cairo_surface_destroy(surface);

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture,
                       &screen_rect,
                       &screen_rect);

        SDL_RenderPresent(renderer);
        a += 1.0f;
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return Val_unit;
}
