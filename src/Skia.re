module Gr = {
  module GLInterface = {
    type t;
  };

  module Context = {
    type t;

    external makeGL: option(GLInterface.t) => t = "caml_GrContext_MakeGL";
  };
};

module Sk = {
  type scalar = float;

  type point = (scalar, scalar);
  type vector = point;

  type budgeted =
    | No
    | Yes;

  module Color = {
    type t;

    external make: (int, int, int, int) => t = "caml_SkColor_make";
  };

  module Matrix = {
    type t;
  };

  module Path = {
    type t;
    // external create: unit => t = "caml_SkPath_create";
    // external copy: t => t = "caml_SkPath_copy";
  };

  module Shader = {
    type t;

    type gradientType =
      | None
      | Color
      | Linear
      | Radial
      | Sweep
      | Conical;

    type tileMode =
      | Clamp
      | Repeat
      | Mirror
      | Decal;
  };

  module Paint = {
    type t;

    type cap =
      | Butt
      | Round
      | Square
      | Default;

    type join =
      | Miter
      | Round
      | Bevel
      | Default;

    type style =
      | Fill
      | Stroke
      | StrokeAndFill;

    external make: unit => t = "caml_SkPaint_make";
    // external shallowCopy: t => t = "caml_SkPaint_shallowCopy";
    // external reset: t => unit = "caml_SkPaint_reset";

    // external getColor: t => Color.t = "caml_SkPaint_getColor";
    external setColor: (t, Color.t) => unit = "caml_SkPaint_setColor";
  };

  module Rect = {
    type t;

    external makeLTRB: (scalar, scalar, scalar, scalar) => t =
      "caml_SkRect_MakeLTRB";
    external makeXYWH: (scalar, scalar, scalar, scalar) => t =
      "caml_SkRect_MakeXYWH";
  };

  module RRect = {
    type t;

    type rRectType =
      | Empty
      | Rect
      | Oval
      | Simple
      | NinePatch
      | Complex;

    external makeRect: Rect.t => t = "caml_SkRRect_MakeRect";
    external makeOval: Rect.t => t = "caml_SkRRect_MakeOval";
    external makeRectXY: (Rect.t, scalar, scalar) => t =
      "caml_SkRRect_MakeRectXY";
    external setRectRadii:
      (t, Rect.t, (vector, vector, vector, vector)) => unit =
      "caml_SkRRect_setRectRadii";
  };

  module Canvas = {
    type t;

    // external save: t => unit = "caml_SkCanvas_save";
    // external translate: (t, scalar, scalar) => unit =
    //   "caml_SkCanvas_translate";
    // external rotate: (t, scalar, scalar, scalar) => unit =
    //   "caml_SkCanvas_rotate";
    external drawPaint: (t, Paint.t) => unit = "caml_SkCanvas_drawPaint";
    external drawRect: (t, Rect.t, Paint.t) => unit = "caml_SkCanvas_drawRect";
    external drawRRect: (t, RRect.t, Paint.t) => unit =
      "caml_SkCanvas_drawRRect";
    // external restore: t => unit = "caml_SkCanvas_restore";
  };

  module Size = {
    type t = {
      w: int,
      h: int,
    };
  };

  module ColorSpace = {
    type t;
  };

  type colorType =
    | Unknown
    | Alpha8
    | RGB565
    | ARGB4444
    | RGBA8888
    | RGB888X
    | BGRA8888
    | RGBA1010102
    | RGB101010X
    | Gray8
    | RGBAF16Norm
    | RGBAF16
    | RGBAF32
    | N32;

  type alphaType =
    | Unknown
    | Opaque
    | Premul
    | Unpremul;

  module ImageInfo = {
    type t;

    external make: (int, int, colorType, alphaType, option(ColorSpace.t)) => t =
      "caml_SkImageInfo_Make";
  };

  module Data = {
    type t;
  };

  module FILEWStream = {
    type t;

    external make: string => t = "caml_SkFILEWStream_make";
    external write: (t, Data.t) => unit = "caml_SkFILEWStream_write"; // TODO proper typing and binding
  };

  module Image = {
    type t;

    external encodeToData: t => Data.t = "caml_SkImage_encodeToData";
  };

  module Surface = {
    type t;

    external makeRenderTarget: (Gr.Context.t, budgeted, ImageInfo.t) => t =
      "caml_SkSurface_MakeRenderTarget";

    external makeRaster: ImageInfo.t => t = "caml_SkSurface_MakeRaster"; // TODO this should accept an optional SurfaceProps parameter

    external getCanvas: t => Canvas.t = "caml_SkSurface_getCanvas";

    external makeImageSnapshot: t => Image.t =
      "caml_SkSurface_makeImageSnapshot";
  };
};