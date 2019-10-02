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

sk_image_t* reason_skia_stub_sk_image_new_from_encoded(const sk_data_t *encoded) {
    printf("DATA: %d\n", encoded);
    sk_image_t* ret = sk_image_new_from_encoded(encoded, NULL);
    printf("RET: %d\n", ret);
    return ret;
};

sk_matrix_t* reason_skia_sk_matrix_new() {
    sk_matrix_t* ret = (sk_matrix_t*)malloc(sizeof(float) * 9);
    return ret;
};

void reason_skia_sk_matrix_destroy(sk_matrix_t* mat) {
    free(mat);
};
