/*
 * Use this file for building any C-layer functionality that we want to keep out of Reason
 */

#include <stdlib.h>
#include <stdio.h>

#include "sk_canvas.h"
#include "sk_data.h"
#include "sk_image.h"
#include "sk_paint.h"
#include "sk_surface.h"
#include "sk_types.h"
#include "sk_typeface.h"

#include <caml/alloc.h>
#include <caml/bigarray.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/threads.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define Val_none Val_int(0)

static value
Val_some( value v )
{   
    CAMLparam1( v );
    CAMLlocal1( some );
    some = caml_alloc(1, 0);
    Store_field( some, 0, v );
    CAMLreturn( some );
}

sk_color_t resk_color_set_argb(value vAlpha, value vRed, value vGreen, value vBlue)
{
    int alpha = Int_val(vAlpha);
    int red = Int_val(vRed);
    int blue = Int_val(vBlue);
    int green = Int_val(vGreen);
    return Val_int(sk_color_set_argb(alpha, red, green, blue));
}

void test_typeface() {
    printf("Hello, world!\n");
  sk_typeface_t *typeface = sk_typeface_create_from_file("/Users/bryphe/reason-skia/example/Orbitron-Medium.ttf", 0); 
  int unitsPerEm = sk_typeface_get_units_per_em(typeface);
    printf("Hello, again: %d\n", unitsPerEm);
  //let maybeTypeface = Typeface.makeFromFile(filePath, 0);
}

#define CONCAT_(a, b) a ## b
#define CONCAT(a, b) CONCAT_(a, b)

#define INIT_STRUCT(TYPENAME) static struct custom_operations CONCAT(TYPENAME, __custom_ops)= { \
    identifier: #TYPENAME, \
    finalize: custom_finalize_default, \
    compare: custom_compare_default, \
    hash: custom_hash_default, \
    serialize: custom_serialize_default, \
    deserialize: custom_deserialize_default \
};

#define ALLOC_STRUCT(TYPENAME, INSTANCE) v = caml_alloc_custom(&CONCAT(TYPENAME, __custom_ops), sizeof(TYPENAME), 0, 1); \
    memcpy(Data_custom_val(v), &INSTANCE, sizeof(TYPENAME));
    
#define STRUCT_VAL(TYPENAME, VALUE) (TYPENAME*)Data_custom_val(VALUE)

typedef struct _surface {
    sk_surface_t *v;
} sk_surface_W;

typedef struct _paint {
   sk_paint_t *v; 
} sk_paint_W;

typedef struct _typeface {
   sk_typeface_t *v; 
} sk_typeface_W;

void resk_finalize_sk_typeface(value vTypeface) {
    sk_typeface_W *typeface = (sk_typeface_W*)Data_custom_val(vTypeface);
    printf("Finalizing typeface: %d\n", typeface->v);
    sk_surface_unref(typeface->v);
    printf("Typeface finalized!\n");
};

void resk_finalize_sk_surface(value vSurface) {
    sk_surface_W *surface = (sk_surface_W*)Data_custom_val(vSurface);
    printf("Finalizing surface: %d\n", surface->v);
    sk_surface_unref(surface->v);
    printf("Surface finalized!\n");
};

void resk_finalize_sk_paint(value vPaint) {
    sk_paint_W *paint = (sk_paint_W*)Data_custom_val(vPaint);
    printf("Finalizing paint: %d\n", paint->v);
    sk_paint_delete(paint->v);
    printf("Paint finalized!\n");
};

static struct custom_operations sk_typeface_custom_ops= {
    identifier: "sk_typeface_t",
    finalize: resk_finalize_sk_typeface,
    compare: custom_compare_default,
    hash: custom_hash_default,
    serialize: custom_serialize_default,
    deserialize: custom_deserialize_default
};

static struct custom_operations sk_surface_custom_ops= {
    identifier: "sk_surface_t",
    finalize: resk_finalize_sk_surface,
    compare: custom_compare_default,
    hash: custom_hash_default,
    serialize: custom_serialize_default,
    deserialize: custom_deserialize_default
};

static struct custom_operations sk_paint_custom_ops= {
    identifier: "sk_paint_t",
    finalize: resk_finalize_sk_paint,
    compare: custom_compare_default,
    hash: custom_hash_default,
    serialize: custom_serialize_default,
    deserialize: custom_deserialize_default
};

INIT_STRUCT(sk_imageinfo_t)
INIT_STRUCT(sk_rect_t)

CAMLprim value resk_imageinfo_make(value vWidth, value vHeight) {
    CAMLparam2(vWidth, vHeight);
    CAMLlocal1(v);

    int width = Int_val(vWidth);
    int height = Int_val(vHeight);

    sk_imageinfo_t imageInfo;
    imageInfo.width = width;
    imageInfo.height = height;
    imageInfo.colorType = RGBA_8888_SK_COLORTYPE;
    imageInfo.alphaType = PREMUL_SK_ALPHATYPE;
    imageInfo.colorspace = NULL;

    v = ALLOC_STRUCT(sk_imageinfo_t, imageInfo);
    CAMLreturn(v);
};

CAMLprim value resk_rect_make(value vLeft, value vTop, value vRight, value vBot) {
    CAMLparam4(vLeft, vTop, vRight, vBot);
    CAMLlocal1(v);
    
    float left = Double_val(vLeft);
    float top = Double_val(vTop);
    float right = Double_val(vRight);
    float bot = Double_val(vBot);

    sk_rect_t rect;
    rect.left = left;
    rect.top = top;
    rect.right = right;
    rect.bottom = bot;

    v = ALLOC_STRUCT(sk_rect_t, rect);
    CAMLreturn(v);
}

CAMLprim value resk_typeface_create_from_file(value vPath, value vIndex) {
    CAMLparam2(vPath, vIndex);
    CAMLlocal2(v, font);

    char *szPath = String_val(vPath);
    int index = Int_val(vIndex);

    sk_typeface_t *pTypeface = sk_typeface_create_from_file(szPath, index);

    if (!pTypeface) {
        v = Val_none;
    } else {
        sk_typeface_W typefaceWrapper;
        typefaceWrapper.v = pTypeface;

        font = caml_alloc_custom(&sk_typeface_custom_ops, sizeof(sk_typeface_W), 0, 1);
        memcpy(Data_custom_val(font), &typefaceWrapper, sizeof(sk_typeface_W));
        v = Val_some(font);
    }
    
    CAMLreturn(v);

}

CAMLprim value resk_typeface_get_units_per_em(value vTypeface) {
    sk_typeface_W* wrappedTypeface = (sk_typeface_W*)Data_custom_val(vTypeface);

    sk_typeface_t *typeface = wrappedTypeface->v;
    int unitsPerEM = sk_typeface_get_units_per_em(typeface);

    return Val_int(unitsPerEM);
}

CAMLprim value resk_paint_make() {
    CAMLparam0();
    CAMLlocal1(v);

    sk_paint_W paintWrapper;
    paintWrapper.v = sk_paint_new();

    v = caml_alloc_custom(&sk_paint_custom_ops, sizeof(sk_paint_W), 0, 1);
    memcpy(Data_custom_val(v), &paintWrapper, sizeof(sk_paint_W));
    CAMLreturn(v);
}

CAMLprim value resk_paint_set_color(value vPaint, value vColor) {
    sk_color_t color = (sk_color_t)Int_val(vColor);
    sk_paint_W* wrappedPaint = (sk_paint_W*)Data_custom_val(vPaint);

    sk_paint_t *paint = wrappedPaint->v;
    sk_paint_set_color(paint, color);
    return Val_unit;
}

CAMLprim value resk_paint_set_antialias(value vPaint, value vAntialias) {
    int antialias = Val_bool(vAntialias);
    sk_paint_W* wrappedPaint = (sk_paint_W*)Data_custom_val(vPaint);

    sk_paint_t *paint = wrappedPaint->v;
    sk_paint_set_antialias(paint, antialias);
    return Val_unit;
}

CAMLprim value resk_paint_set_lcd_render_text(value vPaint, value vLCD) {
    int lcd = Val_bool(vLCD);
    sk_paint_W* wrappedPaint = (sk_paint_W*)Data_custom_val(vPaint);

    sk_paint_t *paint = wrappedPaint->v;
    sk_paint_set_lcd_render_text(paint, lcd);
    return Val_unit;
}

CAMLprim value resk_paint_set_subpixel_text(value vPaint, value vSubpixel) {
    int subpixel = Val_bool(vSubpixel);
    sk_paint_W* wrappedPaint = (sk_paint_W*)Data_custom_val(vPaint);

    sk_paint_t *paint = wrappedPaint->v;
    sk_paint_set_subpixel_text(paint, subpixel);
    return Val_unit;
}

CAMLprim value resk_surface_new_raster(value vImageInfo) {
    CAMLparam1(vImageInfo);
    CAMLlocal1(v);

    sk_imageinfo_t* imageInfo = STRUCT_VAL(sk_imageinfo_t, vImageInfo);
    
    sk_surfaceprops_t* surfaceProps = sk_surfaceprops_new(0,
        RGB_H_SK_PIXELGEOMETRY
        );

    sk_surface_t *surface = sk_surface_new_raster(
        imageInfo,
        0,
        surfaceProps);

    sk_surface_W surfaceWrapper;
    surfaceWrapper.v = surface;
    v = caml_alloc_custom(&sk_surface_custom_ops, sizeof(sk_surface_W), 0, 1);
    memcpy(Data_custom_val(v), &surfaceWrapper, sizeof(sk_surface_W));
    printf("Surface created: %d\n", surface);
    CAMLreturn(v);
}

CAMLprim value resk_surface_get_canvas(value vSurface) {
    CAMLparam1(vSurface);

    sk_surface_W *wrapper = ((sk_surface_W*)Data_custom_val(vSurface));
    sk_surface_t *pSurface = wrapper->v;
    sk_canvas_t *pCanvas = sk_surface_get_canvas(pSurface);
    printf("Canvas created: %d\n", pCanvas);
    CAMLreturn((value)pCanvas);
};

CAMLprim value resk_canvas_draw_paint(value vCanvas, value vPaint) {

    sk_canvas_t *canvas = (sk_canvas_t *)vCanvas;
    sk_paint_W *wrappedPaint = (sk_paint_W*)Data_custom_val(vPaint);
    sk_paint_t *paint = wrappedPaint->v;

    sk_canvas_draw_paint(canvas, paint);

    return Val_unit;
}

CAMLprim value resk_canvas_draw_rect(value vCanvas, value vRect, value vPaint) {
    sk_canvas_t *canvas = (sk_canvas_t *)vCanvas;
    sk_paint_W *wrappedPaint = (sk_paint_W*)Data_custom_val(vPaint);
    sk_paint_t *paint = wrappedPaint->v;
}

CAMLprim value test_api(value vCanvas) {
    CAMLparam1(vCanvas);

    // Check if freetype supports LCD rendering...
    FT_Library library;
    FT_Init_FreeType(&library);
    int result = FT_Library_SetLcdFilter(library, 1);
    printf("FreeType initialization result: %d\n", result);

    //sk_imageinfo_t* imageInfo = (sk_imageinfo_t*)Data_custom_val(vImageInfo);
    /*printf("Creating image info...\n");
    sk_imageinfo_t* imageInfo= (sk_imageinfo_t *)malloc(sizeof(sk_imageinfo_t));
    imageInfo->height = 256l;
    imageInfo->width = 256l;
    imageInfo->colorType = RGBA_8888_SK_COLORTYPE;
    imageInfo->alphaType = PREMUL_SK_ALPHATYPE;
    imageInfo->colorspace = NULL;
    printf("ImageInfo created\n");*/

    //sk_canvas_t *canvas = sk_surface_get_canvas(surface);
    sk_canvas_t *canvas = (sk_canvas_t *)vCanvas;

    //sk_paint_t *paint = sk_paint_new();
    sk_color_t colorWhite = sk_color_set_argb(255, 255, 255, 255);

    //sk_canvas_draw_paint(canvas, paint);
    printf("Painted background\n");

    //sk_typeface_t *typeface = sk_typeface_create_from_file("/Users/bryphe/reason-skia/example/Orbitron-Medium.ttf", 0); 
    sk_fontstyle_t *fontstyle = sk_fontstyle_new(0, 0, 0);
    sk_typeface_t *typeface = sk_typeface_create_from_name_with_font_style("Menlo", fontstyle);
    int unitsPerEM = sk_typeface_get_units_per_em(typeface);
    printf("Units per EM: %d\n", unitsPerEM);

    sk_paint_t *paintText = sk_paint_new();
    sk_paint_set_color(paintText, colorWhite);
    sk_paint_set_antialias(paintText, true);
    sk_paint_set_lcd_render_text(paintText, true);
    sk_paint_set_subpixel_text(paintText, true);
    sk_paint_set_typeface(paintText, typeface);
    sk_paint_set_textsize(paintText, 15.0);
    char *sz = "Hello, world!";
    sk_canvas_draw_text(canvas, sz, strlen(sz), 50.0, 100.0, paintText);

    CAMLreturn(Val_unit);
};

CAMLprim value test_write_surface(value vSurface) {
    CAMLparam1(vSurface);
    sk_surface_W *wrapper = ((sk_surface_W*)Data_custom_val(vSurface));
    sk_surface_t *surface = wrapper->v;
    sk_image_t *image = sk_surface_new_image_snapshot(surface);
    printf("Created image snapshot: %d\n", image);

    sk_data_t *data = sk_image_encode(image);
    printf("Encoded image\n");

    char* dataString = (char *)sk_data_get_data(data);
    size_t dataSize = sk_data_get_size(data);
    printf("Datastring: %d (size: %d)\n", dataString, dataSize);
    FILE* fp = fopen("test_out.png", "w");
    printf("Opened file...\n");
    for (int i = 0; i < dataSize; i++) {
        fputc(dataString[i], fp);
    }
    //fprintf(fp, "%s", dataString);
    fclose(fp);
    
    CAMLreturn(Val_unit);
}
