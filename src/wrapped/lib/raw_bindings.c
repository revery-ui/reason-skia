
/*
 * Use this file for any manual, raw bindings - ie,
 * ones that use [@noalloc], [@unboxed].
 */

#include "c_stubs.h"
#include "sk_canvas.h"
#include "sk_matrix.h"
#include "sk_paint.h"
#include "sk_types.h"

#include <stdlib.h>
#include <stdio.h>

#include "ctypes_cstubs_internals.h"

uint32_t reason_skia_stub_sk_color_get_a(int32_t color) {
    return (uint32_t)sk_color_get_a(color);
}

CAMLprim value reason_skia_stub_sk_color_get_a_byte(value vColor) {
   return Val_int(reason_skia_stub_sk_color_get_a(
       Int_val(vColor)
   ));
}

uint32_t reason_skia_stub_sk_color_get_r(int32_t color) {
    return (uint32_t)sk_color_get_r(color);
}

CAMLprim value reason_skia_stub_sk_color_get_r_byte(value vColor) {
   return Val_int(reason_skia_stub_sk_color_get_r(
       Int_val(vColor)
   ));
}

uint32_t reason_skia_stub_sk_color_get_g(int32_t color) {
    return (uint32_t)sk_color_get_g(color);
}

CAMLprim value reason_skia_stub_sk_color_get_g_byte(value vColor) {
   return Val_int(reason_skia_stub_sk_color_get_g(
       Int_val(vColor)
   ));
}

uint32_t reason_skia_stub_sk_color_get_b(int32_t color) {
    return (uint32_t)sk_color_get_b(color);
}


CAMLprim value reason_skia_stub_sk_color_get_b_byte(value vColor) {
   return Val_int(reason_skia_stub_sk_color_get_b(
       Int_val(vColor)
   ));
}

uint32_t reason_skia_stub_sk_color_set_argb(
   int32_t alpha, 
   int32_t red, 
   int32_t green, 
   int32_t blue)
{
    return (uint32_t)sk_color_set_argb(alpha, red, green, blue);
}

CAMLprim value reason_skia_stub_sk_color_set_argb_byte(
   value vAlpha,
   value vRed,
   value vGreen,
   value vBlue
) {
   return Val_int(reason_skia_stub_sk_color_set_argb(
       Int_val(vAlpha),
       Int_val(vRed),
       Int_val(vGreen),
       Int_val(vBlue)
   ));
}

double reason_skia_rect_get_bottom(
   value vRect
) {
   sk_rect_t *pRect = CTYPES_ADDR_OF_FATPTR(vRect);
   return (double)pRect->bottom;
}

CAMLprim value reason_skia_rect_get_bottom_byte(
   value vRect
) {
   return caml_copy_double(reason_skia_rect_get_bottom(vRect));
}

double reason_skia_rect_get_right(
   value vRect
) {
   sk_rect_t *pRect = CTYPES_ADDR_OF_FATPTR(vRect);
   return (double)pRect->right;
}

CAMLprim value reason_skia_rect_get_right_byte(
   value vRect
) {
   return caml_copy_double(reason_skia_rect_get_right(vRect));
}

double reason_skia_rect_get_top(
   value vRect
) {
   sk_rect_t *pRect = CTYPES_ADDR_OF_FATPTR(vRect);
   return (double)pRect->top;
}

CAMLprim value reason_skia_rect_get_top_byte(
   value vRect
) {
   return caml_copy_double(reason_skia_rect_get_top(vRect));
}

double reason_skia_rect_get_left(
   value vRect
) {
   sk_rect_t *pRect = CTYPES_ADDR_OF_FATPTR(vRect);
   return (double)pRect->left;
}

CAMLprim value reason_skia_rect_get_left_byte(
   value vRect
) {
   return caml_copy_double(reason_skia_rect_get_left(vRect));
}

CAMLprim value reason_skia_rect_set(
   value vRect,
   double left,
   double top,
   double right,
   double bottom
) {
   sk_rect_t *pRect = CTYPES_ADDR_OF_FATPTR(vRect);
   pRect->left = left;
   pRect->top = top;
   pRect->right = right;
   pRect->bottom = bottom;

   return Val_unit;
}

CAMLprim value reasion_skia_rect_set_byte(
   value vRect,
   value vLeft,
   value vTop,
   value vRight,
   value vBottom
) {
   return reason_skia_rect_set(vRect,
   Double_val(vLeft),
   Double_val(vTop),
   Double_val(vRight),
   Double_val(vBottom));
}

CAMLprim value reason_skia_matrix_set_scale(
value vMatrix,
double scaleX,
double scaleY,
double pivotX,
double pivotY) {
   float* pMatrix = CTYPES_ADDR_OF_FATPTR(vMatrix);
   pMatrix[0] = scaleX;
   pMatrix[1] = 0.0;
   pMatrix[2] = pivotX - (scaleX * pivotX);
   pMatrix[3] = 0.0;
   pMatrix[4] = scaleY;
   pMatrix[5] = pivotY - (scaleY * pivotY);
   pMatrix[6] = 0.0;
   pMatrix[7] = 0.0;
   pMatrix[8] = 1.0;
   return Val_unit;
}

CAMLprim value reason_skia_matrix_set_scale_byte(
	value vMatrix,
	value vScaleX,
	value vScaleY,
	value vPivotX,
	value vPivotY) {
	return reason_skia_matrix_set_scale(vMatrix,
	Double_val(vScaleX),
	Double_val(vScaleY),
	Double_val(vPivotX),
	Double_val(vPivotY));
}

CAMLprim value reason_skia_matrix_set_translate(
value vMatrix,
double translateX,
double translateY) {
   float* pMatrix = CTYPES_ADDR_OF_FATPTR(vMatrix);
   pMatrix[0] = 1.0;
   pMatrix[1] = 0.0;
   pMatrix[2] = translateX;
   pMatrix[3] = 0.0;
   pMatrix[4] = 1.0;
   pMatrix[5] = translateY;
   pMatrix[6] = 0.0;
   pMatrix[7] = 0.0;
   pMatrix[8] = 1.0;
   return Val_unit;
}

CAMLprim value reason_skia_matrix_set_translate_byte(
	value vMatrix,
	value vTranslateX,
	value vTranslateY) {
	return reason_skia_matrix_set_translate(vMatrix,
	Double_val(vTranslateX),
	Double_val(vTranslateY));
}
