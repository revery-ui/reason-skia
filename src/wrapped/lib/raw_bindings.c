/*
 * Use this file for building any C-layer functionality that we want to keep out of Reason
 */

#include "c_stubs.h"
#include "sk_canvas.h"
#include "sk_paint.h"
#include "sk_types.h"

#include <stdlib.h>
#include <stdio.h>

#include "ctypes_cstubs_internals.h"

CAMLprim value reason_skia_raw_binding_test(value vCanvas) {
   //CAMLparam1(vCanvas);
   printf("Got here...\n");
   void* pCanvas = CTYPES_ADDR_OF_FATPTR(vCanvas);
   printf("Fake canvas: %p\n", pCanvas);
   printf("And here...\n");
   return Val_unit;
   //CAMLreturn(Val_unit);
}


