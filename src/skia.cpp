#include <stdio.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/bigarray.h>

#include "cxx_wrapped.h"

#include "GrContext.h"
#include "gl/GrGLInterface.h"
#include "SkData.h"
#include "SkImage.h"
#include "SkStream.h"
#include "SkSurface.h"
#include "SkTypeface.h"
#include "SkFont.h"
#include "SkTextBlob.h"
#include "SkBlurTypes.h"
#include "SkMaskFilter.h"

#define Val_none Val_int(0)

CAMLprim value
Val_some(value v)
{
    CAMLparam1(v);
    CAMLlocal1(some);
    some = caml_alloc_small(1, 0);
    Field(some, 0) = v;
    CAMLreturn(some);
}

#define Some_val(v) Field(v, 0)

typedef wrapped<sk_sp<GrGLInterface>> wGrGLInterface;
template <>
char const *ml_name<wGrGLInterface::type>() { return "sk_sp<GrGLInterface>"; }

typedef wrapped<sk_sp<GrContext>> wGrContext;
template <>
char const *ml_name<wGrContext::type>() { return "sk_sp<GrContext>"; }

typedef wrapped<sk_sp<SkSurface>> wSkSurface;
template <>
char const *ml_name<wSkSurface::type>() { return "sk_sp<SkSurface>"; }

typedef wrapped<sk_sp<SkImage>> wSkImage;
template <>
char const *ml_name<wSkImage::type>() { return "sk_sp<SkImage>"; }

typedef wrapped<sk_sp<SkData>> wSkData;
template <>
char const *ml_name<wSkData::type>() { return "sk_sp<SkData>"; }

typedef wrapped<sk_sp<SkColorSpace>> wSkColorSpace;
template <>
char const *ml_name<wSkColorSpace::type>() { return "sk_sp<SkColorSpace>"; }

typedef wrapped<sk_sp<SkTypeface>> wSkTypeface;
template <>
char const *ml_name<wSkTypeface::type>() { return "sk_sp<SkTypeface>"; }

typedef wrapped<sk_sp<SkTextBlob>> wSkTextBlob;
template <>
char const *ml_name<wSkTextBlob::type>() { return "sk_sp<SkTextBlob>"; }

typedef wrapped<sk_sp<SkMaskFilter>> wSkMaskFilter;
template <>
char const *ml_name<wSkMaskFilter::type>() { return "sk_sp<SkMaskFilter>"; }

struct custom_operations ImageInfoCustomOperations = {.identifier = const_cast<char *>("SkImageInfo")};

struct custom_operations SurfacePropsCustomOperations = {.identifier = const_cast<char *>("SkSurfaceProps")};

struct custom_operations RectCustomOperations = {.identifier = const_cast<char *>("SkRect")};

struct custom_operations RRectCustomOperations = {.identifier = const_cast<char *>("SkRRect")};

struct custom_operations FontCustomOperations = {.identifier = const_cast<char *>("SkFont")};

struct custom_operations PaintCustomOperations = {.identifier = const_cast<char *>("SkPaint")};

struct custom_operations ColorCustomOperations = {.identifier = const_cast<char *>("SkColor")};

struct custom_operations FILEWStreamCustomOperations = {.identifier = const_cast<char *>("FILEWStream")};

void warn(const char *message)
{
    printf("[WARNING]: %s\n", message);
}

extern "C"
{
    CAMLprim value
    caml_SkColor_make(value vAlpha, value vRed, value vGreen, value vBlue)
    {
        CAMLparam4(vAlpha, vRed, vGreen, vBlue);
        CAMLlocal1(vColor);
        vColor = caml_alloc_custom(&ColorCustomOperations, sizeof(SkColor), 0, 1);
        auto pColor = static_cast<SkColor *>(Data_custom_val(vColor));
        *pColor = SkColorSetARGB(Int_val(vAlpha), Int_val(vRed), Int_val(vGreen), Int_val(vBlue));
        CAMLreturn(vColor);
    }

    SkBlurStyle variantToBlurType(value vBlurType)
    {
        switch (Int_val(vBlurType))
        {
        case 0:
            return SkBlurStyle::kNormal_SkBlurStyle;
        case 1:
            return SkBlurStyle::kSolid_SkBlurStyle;
        case 2:
            return SkBlurStyle::kOuter_SkBlurStyle;
        case 3:
            return SkBlurStyle::kInner_SkBlurStyle;
        default:
            warn("Unexpected option for blurType");
            return SkBlurStyle::kNormal_SkBlurStyle;
        }
    }

    CAMLprim value
    caml_SkMaskFilter_MakeBlur(value vBlurType, value vSigma)
    {
        CAMLparam2(vBlurType, vSigma);
        auto blurType = variantToBlurType(vBlurType);
        auto sigma = static_cast<SkScalar>(Double_val(vSigma));
        auto maskFilter = SkMaskFilter::MakeBlur(blurType, sigma);
        CAMLreturn(wSkMaskFilter::alloc(maskFilter));
    }

    CAMLprim value
    caml_SkPaint_make(value vUnit)
    {
        CAMLparam1(vUnit);
        CAMLlocal1(vPaint);
        vPaint = caml_alloc_custom(&PaintCustomOperations, sizeof(SkPaint), 0, 1);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        new (pPaint) SkPaint();
        CAMLreturn(vPaint);
    }

    CAMLprim value
    caml_SkPaint_setColor(value vPaint, value vColor)
    {
        CAMLparam2(vPaint, vColor);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto pColor = static_cast<SkColor *>(Data_custom_val(vColor));
        pPaint->setColor(*pColor);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getColor(value vPaint)
    {
        CAMLparam1(vPaint);
        CAMLlocal1(vColor);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        vColor = caml_alloc_custom(&ColorCustomOperations, sizeof(SkColor), 0, 1);
        auto pColor = static_cast<SkColor *>(Data_custom_val(vColor));
        *pColor = pPaint->getColor();
        CAMLreturn(vColor);
    }

    CAMLprim value
    caml_SkPaint_setStrokeWidth(value vPaint, value vStrokeWidth)
    {
        CAMLparam2(vPaint, vStrokeWidth);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto strokeWidth = static_cast<SkScalar>(Double_val(vStrokeWidth));
        pPaint->setStrokeWidth(strokeWidth);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getStrokeWidth(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        CAMLreturn(caml_copy_double(static_cast<double>(pPaint->getStrokeWidth())));
    }

    CAMLprim value
    strokeCapToVariant(SkPaint::Cap strokeCap)
    {
        switch (strokeCap)
        {
        case SkPaint::Cap::kButt_Cap:
            return Val_int(0);
        case SkPaint::Cap::kRound_Cap:
            return Val_int(1);
        case SkPaint::Cap::kSquare_Cap:
            return Val_int(2);
        default:
            warn("Unexpected option for strokeCap");
            return Val_int(0);
        }
    }

    SkPaint::Cap variantToStrokeCap(value vStrokeCap)
    {
        switch (Int_val(vStrokeCap))
        {
        case 0:
            return SkPaint::Cap::kButt_Cap;
        case 1:
            return SkPaint::Cap::kRound_Cap;
        case 2:
            return SkPaint::Cap::kSquare_Cap;
        default:
            warn("Unexpected option for strokeCap");
            return SkPaint::Cap::kDefault_Cap;
        }
    }

    CAMLprim value
    caml_SkPaint_setStrokeCap(value vPaint, value vStrokeCap)
    {
        CAMLparam2(vPaint, vStrokeCap);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto strokeCap = variantToStrokeCap(vStrokeCap);
        pPaint->setStrokeCap(strokeCap);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getStrokeCap(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        CAMLreturn(strokeCapToVariant(pPaint->getStrokeCap()));
    }

    CAMLprim value
    strokeJoinToVariant(SkPaint::Join strokeJoin)
    {
        switch (strokeJoin)
        {
        case SkPaint::Join::kMiter_Join:
            return Val_int(0);
        case SkPaint::Join::kRound_Join:
            return Val_int(1);
        case SkPaint::Join::kBevel_Join:
            return Val_int(2);
        default:
            warn("Unexpected option for strokeJoin");
            return Val_int(0);
        }
    }

    SkPaint::Join variantToStrokeJoin(value vStrokeJoin)
    {
        switch (Int_val(vStrokeJoin))
        {
        case 0:
            return SkPaint::Join::kMiter_Join;
        case 1:
            return SkPaint::Join::kRound_Join;
        case 2:
            return SkPaint::Join::kBevel_Join;
        default:
            warn("Unexpected option for strokeJoin");
            return SkPaint::Join::kDefault_Join;
        }
    }

    CAMLprim value
    caml_SkPaint_setStrokeJoin(value vPaint, value vStrokeJoin)
    {
        CAMLparam2(vPaint, vStrokeJoin);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto strokeJoin = variantToStrokeJoin(vStrokeJoin);
        pPaint->setStrokeJoin(strokeJoin);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getStrokeJoin(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        CAMLreturn(strokeJoinToVariant(pPaint->getStrokeJoin()));
    }

    CAMLprim value
    caml_SkPaint_setStrokeMiter(value vPaint, value vStrokeMiter)
    {
        CAMLparam2(vPaint, vStrokeMiter);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto strokeMiter = static_cast<SkScalar>(Double_val(vStrokeMiter));
        pPaint->setStrokeMiter(strokeMiter);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getStrokeMiter(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        CAMLreturn(caml_copy_double(static_cast<double>(pPaint->getStrokeMiter())));
    }

    CAMLprim value
    styleToVariant(SkPaint::Style style)
    {
        switch (style)
        {
        case SkPaint::Style::kFill_Style:
            return Val_int(0);
        case SkPaint::Style::kStroke_Style:
            return Val_int(1);
        case SkPaint::Style::kStrokeAndFill_Style:
            return Val_int(2);
        default:
            warn("Unexpected option for style");
            return Val_int(0);
        }
    }

    SkPaint::Style variantToStyle(value vStyle)
    {
        switch (Int_val(vStyle))
        {
        case 0:
            return SkPaint::Style::kFill_Style;
        case 1:
            return SkPaint::Style::kStroke_Style;
        case 2:
            return SkPaint::Style::kStrokeAndFill_Style;
        default:
            warn("Unexpected option for style");
            return SkPaint::Style::kFill_Style;
        }
    }

    CAMLprim value
    caml_SkPaint_setStyle(value vPaint, value vStyle)
    {
        CAMLparam2(vPaint, vStyle);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto style = variantToStyle(vStyle);
        pPaint->setStyle(style);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getStyle(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        CAMLreturn(styleToVariant(pPaint->getStyle()));
    }

    CAMLprim value
    caml_SkPaint_setAntiAlias(value vPaint, value vShouldBeEnabled)
    {
        CAMLparam2(vPaint, vShouldBeEnabled);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto shouldBeEnabled = Bool_val(vShouldBeEnabled);
        pPaint->setAntiAlias(shouldBeEnabled);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_isAntiAlias(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto isEnabled = pPaint->isAntiAlias();
        CAMLreturn(Val_bool(isEnabled));
    }

    CAMLprim value
    caml_SkPaint_setMaskFilter(value vPaint, value vMaskFilter)
    {
        CAMLparam2(vPaint, vMaskFilter);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto maskFilter = wSkMaskFilter::get(vMaskFilter);
        pPaint->setMaskFilter(maskFilter);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkPaint_getMaskFilter(value vPaint)
    {
        CAMLparam1(vPaint);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        auto maskFilter = pPaint->getMaskFilter();
        CAMLreturn(wSkMaskFilter::alloc(maskFilter));
    }

    CAMLprim value
    caml_SkTypeface_MakeDefault(value vUnit)
    {
        CAMLparam1(vUnit);
        auto typeface = SkTypeface::MakeDefault();
        CAMLreturn(wSkTypeface::alloc(typeface));
    }

    CAMLprim value
    caml_SkFont_Make(value vTypeface, value vSize, value vScaleX, value vSkewX)
    {
        CAMLparam4(vTypeface, vSize, vScaleX, vSkewX);
        CAMLlocal1(vFont);
        auto typeface = wSkTypeface::get(vTypeface);
        auto size = static_cast<SkScalar>(Double_val(vSize));
        auto scaleX = static_cast<SkScalar>(Double_val(vScaleX));
        auto skewX = static_cast<SkScalar>(Double_val(vSkewX));
        vFont = caml_alloc_custom(&FontCustomOperations, sizeof(SkFont), 0, 1);
        auto pFont = static_cast<SkFont *>(Data_custom_val(vFont));
        new (pFont) SkFont(typeface, size, scaleX, skewX);
        CAMLreturn(vFont);
    }

    CAMLprim value
    caml_SkFont_setSubpixel(value vFont, value vShouldBeEnabled)
    {
        CAMLparam2(vFont, vShouldBeEnabled);
        auto pFont = static_cast<SkFont *>(Data_custom_val(vFont));
        auto shouldBeEnabled = Bool_val(vShouldBeEnabled);
        pFont->setSubpixel(shouldBeEnabled);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkFont_isSubpixel(value vFont)
    {
        CAMLparam1(vFont);
        auto pFont = static_cast<SkFont *>(Data_custom_val(vFont));
        auto isEnabled = pFont->isSubpixel();
        CAMLreturn(Val_bool(isEnabled));
    }

    CAMLprim value
    edgingToVariant(SkFont::Edging edging)
    {
        switch (edging)
        {
        case SkFont::Edging::kAlias:
            return Val_int(0);
        case SkFont::Edging::kAntiAlias:
            return Val_int(1);
        case SkFont::Edging::kSubpixelAntiAlias:
            return Val_int(2);
        default:
            warn("Unexpected option for edging");
            return Val_int(0);
        }
    }

    SkFont::Edging variantToEdging(value vEdging)
    {
        switch (Int_val(vEdging))
        {
        case 0:
            return SkFont::Edging::kAlias;
        case 1:
            return SkFont::Edging::kAntiAlias;
        case 2:
            return SkFont::Edging::kSubpixelAntiAlias;
        default:
            warn("Unexpected option for edging");
            return SkFont::Edging::kAlias;
        }
    }

    CAMLprim value
    caml_SkFont_setEdging(value vFont, value vEdging)
    {
        CAMLparam2(vFont, vEdging);
        auto pFont = static_cast<SkFont *>(Data_custom_val(vFont));
        auto edging = variantToEdging(vEdging);
        pFont->setEdging(edging);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkFont_getEdging(value vFont)
    {
        CAMLparam1(vFont);
        CAMLlocal1(vEdging);
        auto pFont = static_cast<SkFont *>(Data_custom_val(vFont));
        auto edging = pFont->getEdging();
        vEdging = edgingToVariant(edging);
        CAMLreturn(vEdging);
    }

    SkTextEncoding variantToTextEncoding(value vEncoding)
    {
        switch (Int_val(vEncoding))
        {
        case 0:
            return SkTextEncoding::kUTF8;
        case 1:
            return SkTextEncoding::kUTF16;
        case 2:
            return SkTextEncoding::kUTF32;
        case 3:
            return SkTextEncoding::kGlyphID;
        default:
            warn("Unexpected option for encoding");
            return SkTextEncoding::kUTF8;
        }
    }

    CAMLprim value
    caml_SkTextBlob_MakeFromString(value vString, value vFont, value vEncodingOption)
    {
        CAMLparam3(vString, vFont, vEncodingOption);
        auto string = String_val(vString);
        auto pFont = static_cast<SkFont *>(Data_custom_val(vFont));
        auto textBlob = vEncodingOption == Val_none
                            ? SkTextBlob::MakeFromString(string, *pFont)
                            : SkTextBlob::MakeFromString(string, *pFont, variantToTextEncoding(Some_val(vEncodingOption)));
        CAMLreturn(wSkTextBlob::alloc(textBlob));
    }

    SkBudgeted variantToBudgeted(value vBudgeted)
    {
        switch (Int_val(vBudgeted))
        {
        case 0:
            return SkBudgeted::kNo;
        case 1:
            return SkBudgeted::kYes;
        default:
            warn("Unexpected option for budgeted");
            return SkBudgeted::kNo;
        }
    }

    SkColorType variantToColorType(value vColorType)
    {
        switch (Int_val(vColorType))
        {
        case 0:
            return kUnknown_SkColorType;
        case 1:
            return kAlpha_8_SkColorType;
        case 2:
            return kRGB_565_SkColorType;
        case 3:
            return kARGB_4444_SkColorType;
        case 4:
            return kRGBA_8888_SkColorType;
        case 5:
            return kRGB_888x_SkColorType;
        case 6:
            return kBGRA_8888_SkColorType;
        case 7:
            return kRGBA_1010102_SkColorType;
        case 8:
            return kRGB_101010x_SkColorType;
        case 9:
            return kGray_8_SkColorType;
        case 10:
            return kRGBA_F16Norm_SkColorType;
        case 11:
            return kRGBA_F16_SkColorType;
        case 12:
            return kRGBA_F32_SkColorType;
        case 13:
            return kN32_SkColorType;
        default:
            warn("Unexpected option for colorType");
            return kUnknown_SkColorType;
        }
    }

    SkAlphaType variantToAlphaType(value vAlphaType)
    {
        switch (Int_val(vAlphaType))
        {
        case 0:
            return kUnknown_SkAlphaType;
        case 1:
            return kOpaque_SkAlphaType;
        case 2:
            return kPremul_SkAlphaType;
        case 3:
            return kUnpremul_SkAlphaType;
        default:
            warn("Unexpected option for colorType");
            return kUnknown_SkAlphaType;
        }
    }

    CAMLprim value
    caml_GrContext_MakeGL(value vGrGLInterfaceOption)
    {
        CAMLparam1(vGrGLInterfaceOption);
        auto context = vGrGLInterfaceOption == Val_none
                           ? GrContext::MakeGL(nullptr)
                           : GrContext::MakeGL(wGrGLInterface::get(Val_some(vGrGLInterfaceOption)));
        CAMLreturn(wGrContext::alloc(context));
    }

    CAMLprim value
    caml_SkRect_MakeLTRB(value vL, value vT, value vR, value vB)
    {
        CAMLparam4(vL, vT, vR, vB);
        CAMLlocal1(vRect);
        vRect = caml_alloc_custom(&RectCustomOperations, sizeof(SkRect), 0, 1);
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        *pRect = SkRect::MakeLTRB(
            static_cast<SkScalar>(Double_val(vL)),
            static_cast<SkScalar>(Double_val(vT)),
            static_cast<SkScalar>(Double_val(vR)),
            static_cast<SkScalar>(Double_val(vB)));
        CAMLreturn(vRect);
    }

    CAMLprim value
    caml_SkRect_MakeXYWH(value vX, value vY, value vW, value vH)
    {
        CAMLparam4(vX, vY, vW, vH);
        CAMLlocal1(vRect);
        vRect = caml_alloc_custom(&RectCustomOperations, sizeof(SkRect), 0, 1);
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        *pRect = SkRect::MakeXYWH(
            static_cast<SkScalar>(Double_val(vX)),
            static_cast<SkScalar>(Double_val(vY)),
            static_cast<SkScalar>(Double_val(vW)),
            static_cast<SkScalar>(Double_val(vH)));
        CAMLreturn(vRect);
    }

    CAMLprim value
    caml_SkRRect_MakeRect(value vRect)
    {
        CAMLparam1(vRect);
        CAMLlocal1(vRRect);
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        vRRect = caml_alloc_custom(&RRectCustomOperations, sizeof(SkRRect), 0, 1);
        auto pRRect = static_cast<SkRRect *>(Data_custom_val(vRRect));
        *pRRect = SkRRect::MakeRect(*pRect);
        CAMLreturn(vRRect);
    }

    CAMLprim value
    caml_SkRRect_MakeOval(value vRect)
    {
        CAMLparam1(vRect);
        CAMLlocal1(vRRect);
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        vRRect = caml_alloc_custom(&RRectCustomOperations, sizeof(SkRRect), 0, 1);
        auto pRRect = static_cast<SkRRect *>(Data_custom_val(vRRect));
        *pRRect = SkRRect::MakeOval(*pRect);
        CAMLreturn(vRRect);
    }

    CAMLprim value
    caml_SkRRect_MakeRectXY(value vRect, value vX, value vY)
    {
        CAMLparam3(vRect, vX, vY);
        CAMLlocal1(vRRect);
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        vRRect = caml_alloc_custom(&RRectCustomOperations, sizeof(SkRRect), 0, 1);
        auto pRRect = static_cast<SkRRect *>(Data_custom_val(vRRect));
        *pRRect = SkRRect::MakeRectXY(
            *pRect,
            static_cast<SkScalar>(Double_val(vX)),
            static_cast<SkScalar>(Double_val(vY)));
        CAMLreturn(vRRect);
    }

    CAMLprim value
    caml_SkRRect_setRectRadii(value vRRect, value vRect, value vRadii)
    {
        CAMLparam3(vRRect, vRect, vRadii);
        CAMLlocal4(vTopLeftRadii, vTopRightRadii, vBottomRightRadii, vBottomLeftRadii);
        auto pRRect = static_cast<SkRRect *>(Data_custom_val(vRRect));
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        vTopLeftRadii = Field(vRadii, 0);
        vTopRightRadii = Field(vRadii, 1);
        vBottomRightRadii = Field(vRadii, 2);
        vBottomLeftRadii = Field(vRadii, 3);
        struct Radii
        {
            SkVector vectors[4];
        };
        Radii radii = {{
            {static_cast<SkScalar>(Double_val(Field(vTopLeftRadii, 0))), static_cast<SkScalar>(Double_val(Field(vTopLeftRadii, 1)))},
            {static_cast<SkScalar>(Double_val(Field(vTopRightRadii, 0))), static_cast<SkScalar>(Double_val(Field(vTopRightRadii, 1)))},
            {static_cast<SkScalar>(Double_val(Field(vBottomRightRadii, 0))), static_cast<SkScalar>(Double_val(Field(vBottomRightRadii, 1)))},
            {static_cast<SkScalar>(Double_val(Field(vBottomLeftRadii, 0))), static_cast<SkScalar>(Double_val(Field(vBottomLeftRadii, 1)))},
        }};
        pRRect->setRectRadii(
            *pRect,
            radii.vectors);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkImageInfo_Make(value vWidth, value vHeight, value vColorType, value vAlphaType, value vColorSpaceOption)
    {
        CAMLparam5(vWidth, vHeight, vColorType, vAlphaType, vColorSpaceOption);
        CAMLlocal1(vImageInfo);
        vImageInfo = caml_alloc_custom(&ImageInfoCustomOperations, sizeof(SkImageInfo), 0, 1);
        auto pImageInfo = static_cast<SkImageInfo *>(Data_custom_val(vImageInfo));
        *pImageInfo = vColorSpaceOption == Val_none
                          ? SkImageInfo::Make(
                                Int_val(vWidth),
                                Int_val(vHeight),
                                variantToColorType(vColorType),
                                variantToAlphaType(vAlphaType))
                          : SkImageInfo::Make(
                                Int_val(vWidth),
                                Int_val(vHeight),
                                variantToColorType(vColorType),
                                variantToAlphaType(vAlphaType),
                                wSkColorSpace::get(Val_some(vColorSpaceOption)));
        CAMLreturn(vImageInfo);
    }

    SkPixelGeometry variantToPixelGeometry(value vPixelGeometry)
    {
        switch (Int_val(vPixelGeometry))
        {
        case 0:
            return kUnknown_SkPixelGeometry;
        case 1:
            return kRGB_H_SkPixelGeometry;
        case 2:
            return kBGR_H_SkPixelGeometry;
        case 3:
            return kRGB_V_SkPixelGeometry;
        case 4:
            return kBGR_V_SkPixelGeometry;
        default:
            warn("Unexpected option for pixelGeometry");
            return kUnknown_SkPixelGeometry;
        }
    }

    CAMLprim value
    caml_SkSurfaceProps_Make(value vPixelGeometry)
    {
        CAMLparam1(vPixelGeometry);
        CAMLlocal1(vSurfaceProps);
        auto pixelGeometry = variantToPixelGeometry(vPixelGeometry);
        vSurfaceProps = caml_alloc_custom(&SurfacePropsCustomOperations, sizeof(SkSurfaceProps), 0, 1);
        auto pSurfaceProps = Data_custom_val(vSurfaceProps);
        new (pSurfaceProps) SkSurfaceProps(0, pixelGeometry);
        CAMLreturn(vSurfaceProps);
    }

    CAMLprim value
    caml_SkSurface_MakeRenderTarget(value vContext, value vBudgeted, value vImageInfo)
    {
        CAMLparam3(vContext, vBudgeted, vImageInfo);
        auto context = wGrContext::get(vContext);
        auto budgeted = variantToBudgeted(vBudgeted);
        auto pImageInfo = static_cast<SkImageInfo *>(Data_custom_val(vImageInfo));
        // TODO this can also return null and should probably be an option
        auto surface = SkSurface::MakeRenderTarget(context.get(), budgeted, *pImageInfo);
        CAMLreturn(wSkSurface::alloc(surface));
    }

    CAMLprim value
    caml_SkSurface_MakeRaster(value vImageInfo, value vSurfacePropsOption)
    {
        CAMLparam2(vImageInfo, vSurfacePropsOption);
        auto pImageInfo = static_cast<SkImageInfo *>(Data_custom_val(vImageInfo));
        // TODO this can also return null and should probably be an option
        auto surface = vSurfacePropsOption == Val_none
                           ? SkSurface::MakeRaster(*pImageInfo)
                           : SkSurface::MakeRaster(*pImageInfo, static_cast<SkSurfaceProps *>(Data_custom_val(vSurfacePropsOption)));
        CAMLreturn(wSkSurface::alloc(surface));
    }

    CAMLprim value
    caml_SkSurface_getCanvas(value vSurface)
    {
        CAMLparam1(vSurface);
        auto surface = wSkSurface::get(vSurface);
        SkCanvas *pCanvas = surface->getCanvas();
        CAMLreturn((value)pCanvas);
    }

    CAMLprim value
    caml_SkSurface_makeImageSnapshot(value vSurface)
    {
        CAMLparam1(vSurface);
        auto surface = wSkSurface::get(vSurface);
        auto image = surface->makeImageSnapshot();
        CAMLreturn(wSkImage::alloc(image));
    }

    CAMLprim value
    caml_SkCanvas_drawPaint(value vCanvas, value vPaint)
    {
        CAMLparam2(vCanvas, vPaint);
        auto pCanvas = reinterpret_cast<SkCanvas *>(vCanvas);
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        pCanvas->drawPaint(*pPaint);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkCanvas_drawRect(value vCanvas, value vRect, value vPaint)
    {
        CAMLparam3(vCanvas, vRect, vPaint);
        auto pCanvas = reinterpret_cast<SkCanvas *>(vCanvas);
        auto pRect = static_cast<SkRect *>(Data_custom_val(vRect));
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        pCanvas->drawRect(*pRect, *pPaint);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkCanvas_drawRRect(value vCanvas, value vRRect, value vPaint)
    {
        CAMLparam3(vCanvas, vRRect, vPaint);
        auto pCanvas = reinterpret_cast<SkCanvas *>(vCanvas);
        auto pRRect = static_cast<SkRRect *>(Data_custom_val(vRRect));
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        pCanvas->drawRRect(*pRRect, *pPaint);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkCanvas_drawTextBlob(value vCanvas, value vTextBlob, value vX, value vY, value vPaint)
    {
        CAMLparam5(vCanvas, vTextBlob, vX, vY, vPaint);
        auto pCanvas = reinterpret_cast<SkCanvas *>(vCanvas);
        auto textBlob = wSkTextBlob::get(vTextBlob);
        auto x = static_cast<SkScalar>(Double_val(vX));
        auto y = static_cast<SkScalar>(Double_val(vY));
        auto pPaint = static_cast<SkPaint *>(Data_custom_val(vPaint));
        pCanvas->drawTextBlob(textBlob, x, y, *pPaint);
        CAMLreturn(Val_unit);
    }

    CAMLprim value
    caml_SkImage_encodeToData(value vImage)
    {
        CAMLparam1(vImage);
        auto image = wSkImage::get(vImage);
        auto data = image->encodeToData();
        if (data.get() == nullptr || data == nullptr)
        {
            warn("nullptr was returned!");
        }
        CAMLreturn(wSkData::alloc(data));
    }

    CAMLprim value
    caml_SkFILEWStream_make(value vPath)
    {
        CAMLparam1(vPath);
        CAMLlocal1(vFILEWStream);
        vFILEWStream = caml_alloc_custom(&FILEWStreamCustomOperations, sizeof(SkFILEWStream), 0, 1);
        auto pFILEWStream = static_cast<SkFILEWStream *>(Data_custom_val(vFILEWStream));
        new (pFILEWStream) SkFILEWStream(String_val(vPath));
        CAMLreturn(vFILEWStream);
    }

    CAMLprim value
    caml_SkFILEWStream_write(value vFILEWStream, value vData)
    {
        CAMLparam2(vFILEWStream, vData);
        auto fileWStream = static_cast<SkFILEWStream *>(Data_custom_val(vFILEWStream));
        auto data = wSkData::get(vData);
        fileWStream->write(data->data(), data->size());
        CAMLreturn(Val_unit);
    }
}
