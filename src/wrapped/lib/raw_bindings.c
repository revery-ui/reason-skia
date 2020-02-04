
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

CAMLprim value reason_skia_matrix_set_scale(
value vMatrix,
float scaleX,
float scaleY,
float pivotX,
float pivotY) {
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
float translateX,
float translateY) {
   float* pMatrix = CTYPES_ADDR_OF_FATPTR(vMatrix);
   pMatrix[0] = 0.0;
   pMatrix[1] = 0.0;
   pMatrix[2] = translateX;
   pMatrix[3] = 0.0;
   pMatrix[4] = 0.0;
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
