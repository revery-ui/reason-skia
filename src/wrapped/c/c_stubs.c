/*
 * Use this file for building any C-layer functionality that we want to keep out of Reason
 */

#include "sk_types.h"

sk_color_t reason_skia_stub_sk_color_set_argb(int alpha, int red, int green, int blue)
{
    return sk_color_set_argb(alpha, red, green, blue);
}

uint32_t reason_skia_stub_sk_color_get_a(sk_color_t color)
{
    return sk_color_get_a(color);
}

uint32_t reason_skia_stub_sk_color_get_r(sk_color_t color)
{
    return sk_color_get_r(color);
}

uint32_t reason_skia_stub_sk_color_get_g(sk_color_t color)
{
    return sk_color_get_g(color);
}

uint32_t reason_skia_stub_sk_color_get_b(sk_color_t color)
{
    return sk_color_get_b(color);
}
