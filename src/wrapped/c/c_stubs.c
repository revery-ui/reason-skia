/*
 * Use this file for building any C-layer functionality that we want to keep out of Reason
 */

#include "c_stubs.h"

#include <stdlib.h>


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

void test_typeface() {
    printf("Hello, world!\n");
  sk_typeface_t *typeface = sk_typeface_create_from_file("/Users/bryphe/reason-skia/example/Orbitron-Medium.ttf", 0); 
  int unitsPerEm = sk_typeface_get_units_per_em(typeface);
    printf("Hello, again: %d\n", unitsPerEm);
  //let maybeTypeface = Typeface.makeFromFile(filePath, 0);
}
