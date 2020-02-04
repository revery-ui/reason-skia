#include "sk_canvas.h"
#include "sk_paint.h"
#include "sk_types.h"
#include "gr_context.h"

#include <SDL2/SDL.h>

sk_color_t reason_skia_stub_sk_color_set_argb(int alpha, int red, int green, int blue);

uint32_t reason_skia_stub_sk_color_get_a(sk_color_t color);
uint32_t reason_skia_stub_sk_color_get_r(sk_color_t color);
uint32_t reason_skia_stub_sk_color_get_g(sk_color_t color);
uint32_t reason_skia_stub_sk_color_get_b(sk_color_t color);

void reason_skia_stub_sk_canvas_draw_rect_ltwh(sk_canvas_t *canvas, float left, float top, float width, float height, sk_paint_t* paint);

gr_glinterface_t* reason_skia_make_sdl2_interface();
