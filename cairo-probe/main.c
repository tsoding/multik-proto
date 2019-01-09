#include <stdio.h>
#include <stdlib.h>

#include <cairo.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 80

int main(int argc, char *argv[])
{
    cairo_surface_t *surface =
        cairo_image_surface_create(
            CAIRO_FORMAT_ARGB32,
            SCREEN_WIDTH,
            SCREEN_HEIGHT);
    cairo_t *cr = cairo_create(surface);

    cairo_select_font_face(

        cr, "serif",
        CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 32.0);
    cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);
    cairo_move_to(cr, 10.0, 50.0);
    cairo_show_text(cr, "4HEad");

    cairo_set_source_rgbz(cr, 1.0, 0.0, 0.0);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_curve_to(cr, 0.0, SCREEN_HEIGHT,
                   SCREEN_WIDTH, SCREEN_HEIGHT,
                   SCREEN_WIDTH, 0.0);
    cairo_set_line_width(cr, 5);
    cairo_stroke(cr);

    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, "hello.png");
    cairo_surface_destroy(surface);

    return 0;
}
