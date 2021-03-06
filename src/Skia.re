type colorType = SkiaWrapped.colorType;
type alphaType = SkiaWrapped.alphaType;

module Color = {
  type t = int32;
  [@noalloc]
  external makeArgb:
    ([@unboxed] int32, [@unboxed] int32, [@unboxed] int32, [@unboxed] int32) =>
    [@unboxed] int32 =
    "reason_skia_stub_sk_color_set_argb_byte"
    "reason_skia_stub_sk_color_set_argb";

  [@noalloc]
  external getA: ([@unboxed] int32) => [@unboxed] int32 =
    "reason_skia_stub_sk_color_get_a_byte" "reason_skia_stub_sk_color_get_a";

  [@noalloc]
  external getR: ([@unboxed] int32) => [@unboxed] int32 =
    "reason_skia_stub_sk_color_get_r_byte" "reason_skia_stub_sk_color_get_r";

  [@noalloc]
  external getG: ([@unboxed] int32) => [@unboxed] int32 =
    "reason_skia_stub_sk_color_get_g_byte" "reason_skia_stub_sk_color_get_g";

  [@noalloc]
  external getB: ([@unboxed] int32) => [@unboxed] int32 =
    "reason_skia_stub_sk_color_get_b_byte" "reason_skia_stub_sk_color_get_b";

  module Float = {
    external makeArgb:
      (
        [@unboxed] float,
        [@unboxed] float,
        [@unboxed] float,
        [@unboxed] float
      ) =>
      [@unboxed] int32 =
      "reason_skia_color_float_make_argb_byte"
      "reason_skia_color_float_make_argb";

    [@noalloc]
    external getA: ([@unboxed] int32) => [@unboxed] float =
      "reason_skia_stub_sk_color_float_get_a_byte"
      "reason_skia_stub_sk_color_float_get_a";

    external getR: ([@unboxed] int32) => [@unboxed] float =
      "reason_skia_stub_sk_color_float_get_r_byte"
      "reason_skia_stub_sk_color_float_get_r";

    external getG: ([@unboxed] int32) => [@unboxed] float =
      "reason_skia_stub_sk_color_float_get_g_byte"
      "reason_skia_stub_sk_color_float_get_g";

    external getB: ([@unboxed] int32) => [@unboxed] float =
      "reason_skia_stub_sk_color_float_get_b_byte"
      "reason_skia_stub_sk_color_float_get_b";
  };
};

module FontMetrics = {
  type t = SkiaWrapped.FontMetrics.t;
  let make = SkiaWrapped.FontMetrics.make;

  let getAscent = SkiaWrapped.FontMetrics.getAscent;
  let getDescent = SkiaWrapped.FontMetrics.getDescent;
  let getTop = SkiaWrapped.FontMetrics.getTop;
  let getBottom = SkiaWrapped.FontMetrics.getBottom;
  let getUnderlineThickness = SkiaWrapped.FontMetrics.getUnderlineThickness;
  let getUnderlinePosition = SkiaWrapped.FontMetrics.getUnderlinePosition;
};

module Hinting = {
  type t = SkiaWrapped.Hinting.t;
};

module TextEncoding = {
  type t = SkiaWrapped.TextEncoding.t;
};

module ImageFilter = {
  type t = SkiaWrapped.ImageFilter.t;

  module CropRect = {
    type t = SkiaWrapped.ImageFilter.CropRect.t;
  };

  module DropShadow = {
    type shadowMode = SkiaWrapped.ImageFilter.DropShadow.shadowMode;

    let make =
        (
          dx,
          dy,
          sigmaX,
          sigmaY,
          color,
          shadowMode,
          inputOption,
          cropRectOption,
        ) => {
      let imageFilter =
        SkiaWrapped.ImageFilter.DropShadow.allocate(
          dx,
          dy,
          sigmaX,
          sigmaY,
          // TODO: Make fast
          Unsigned.UInt32.of_int32(color),
          shadowMode,
          inputOption,
          cropRectOption,
        );
      Gc.finalise(SkiaWrapped.ImageFilter.delete, imageFilter);
      imageFilter;
    };
  };

  let makeDropShadow = DropShadow.make;
};

module Paint = {
  type t = SkiaWrapped.Paint.t;
  type style = SkiaWrapped.Paint.style;

  module CI = Cstubs_internals;

  let make = () => {
    let paint = SkiaWrapped.Paint.allocate();
    Gc.finalise(SkiaWrapped.Paint.delete, paint);
    paint;
  };

  let measureText = (paint, text, rectOpt) => {
    SkiaWrapped.Paint.measureText(paint, text, String.length(text), rectOpt);
  };

  [@noalloc]
  external _setColor: (CI.fatptr(_), [@unboxed] int32) => unit =
    "reason_skia_paint_set_color_byte" "reason_skia_paint_set_color";

  [@noalloc]
  external _setAlphaf: (CI.fatptr(_), [@unboxed] float) => unit =
    "reason_skia_paint_set_alphaf_byte" "reason_skia_paint_set_alphaf";

  let setColor = (paint, color) => _setColor(CI.cptr(paint), color);
  let setAlpha = (paint, alpha) => _setAlphaf(CI.cptr(paint), alpha);

  let setHinting = SkiaWrapped.Paint.setHinting;
  let getHinting = SkiaWrapped.Paint.getHinting;

  let isAutohinted = SkiaWrapped.Paint.isAutohinted;
  let setAutohinted = SkiaWrapped.Paint.setAutohinted;

  let setAntiAlias = SkiaWrapped.Paint.setAntiAlias;
  let setStyle = SkiaWrapped.Paint.setStyle;
  let setStrokeWidth = SkiaWrapped.Paint.setStrokeWidth;
  let setLcdRenderText = SkiaWrapped.Paint.setLcdRenderText;
  let setSubpixelText = SkiaWrapped.Paint.setSubpixelText;
  let setTextSize = SkiaWrapped.Paint.setTextSize;
  let setTypeface = SkiaWrapped.Paint.setTypeface;
  let getFontMetrics = SkiaWrapped.Paint.getFontMetrics;
  let setImageFilter = SkiaWrapped.Paint.setImageFilter;
  let setTextEncoding = SkiaWrapped.Paint.setTextEncoding;
  let getTextEncoding = SkiaWrapped.Paint.getTextEncoding;
};

module Point = {
  type t = SkiaWrapped.Point.t;

  let make = SkiaWrapped.Point.make;

  let getX = SkiaWrapped.Point.getX;
  let getY = SkiaWrapped.Point.getY;
};

module Vector = {
  type t = SkiaWrapped.Vector.t;

  let make = SkiaWrapped.Vector.make;

  let getX = SkiaWrapped.Vector.getX;
  let getY = SkiaWrapped.Vector.getY;
};

module Matrix = {
  type t = SkiaWrapped.Matrix.t;

  let make = SkiaWrapped.Matrix.make;
  let setAll = SkiaWrapped.Matrix.setAll;
  let get = SkiaWrapped.Matrix.get;
  let set = SkiaWrapped.Matrix.set;

  module CI = Cstubs_internals;

  [@noalloc]
  external _setScale:
    (
      CI.fatptr(_),
      [@unboxed] float,
      [@unboxed] float,
      [@unboxed] float,
      [@unboxed] float
    ) =>
    unit =
    "reason_skia_matrix_set_scale_byte" "reason_skia_matrix_set_scale";

  [@noalloc]
  external _setTranslate:
    (CI.fatptr(_), [@unboxed] float, [@unboxed] float) => unit =
    "reason_skia_matrix_set_translate_byte" "reason_skia_matrix_set_translate";

  let setScale = (mat, scaleX, scaleY, pivotX, pivotY) =>
    _setScale(CI.cptr(mat), scaleX, scaleY, pivotX, pivotY);

  let setTranslate = (matrix, translateX, translateY) =>
    _setTranslate(CI.cptr(matrix), translateX, translateY);

  let makeAll =
      (
        scaleX,
        skewX,
        translateX,
        skewY,
        scaleY,
        translateY,
        perspective0,
        perspective1,
        perspective2,
      ) => {
    let matrix = make();
    setAll(
      matrix,
      scaleX,
      skewX,
      translateX,
      skewY,
      scaleY,
      translateY,
      perspective0,
      perspective1,
      perspective2,
    );
    matrix;
  };
  let makeScale = (scaleX, scaleY, pivotX, pivotY) => {
    let matrix = make();
    setScale(matrix, scaleX, scaleY, pivotX, pivotY);
    matrix;
  };
  let makeTranslate = (translateX, translateY) => {
    let matrix = make();
    setTranslate(matrix, translateX, translateY);
    matrix;
  };

  let getScaleX = matrix => get(matrix, 0);
  let getScaleY = matrix => get(matrix, 4);
  let getSkewX = matrix => get(matrix, 1);
  let getSkewY = matrix => get(matrix, 3);
  let getTranslateX = matrix => get(matrix, 2);
  let getTranslateY = matrix => get(matrix, 5);
  let getPerspX = matrix => get(matrix, 6);
  let getPerspY = matrix => get(matrix, 7);

  let setScaleX = (matrix, scaleX) => set(matrix, 0, scaleX);
  let setScaleY = (matrix, scaleY) => set(matrix, 4, scaleY);
  let setSkewX = (matrix, skewX) => set(matrix, 1, skewX);
  let setSkewY = (matrix, skewY) => set(matrix, 3, skewY);
  let setTranslateX = (matrix, translateX) => set(matrix, 2, translateX);
  let setTranslateY = (matrix, translateY) => set(matrix, 5, translateY);
  let setPerspX = (matrix, perspectiveX) => set(matrix, 6, perspectiveX);
  let setPerspY = (matrix, perspectiveY) => set(matrix, 7, perspectiveY);
  let setSkew = (matrix, skewX, skewY, pivotX, pivotY) =>
    setAll(
      matrix,
      1.,
      skewX,
      -. skewX *. pivotY,
      skewY,
      1.,
      -. skewY *. pivotX,
      0.,
      0.,
      1.,
    );
  let setIdentity = matrix =>
    setAll(matrix, 1., 0., 0., 0., 1., 0., 0., 0., 1.);
  let reset = setIdentity;

  let invert = SkiaWrapped.Matrix.invert;
  let concat = SkiaWrapped.Matrix.concat;
  let preConcat = SkiaWrapped.Matrix.preConcat;
  let postConcat = SkiaWrapped.Matrix.postConcat;
  let mapRect = SkiaWrapped.Matrix.mapRect;
  let mapPoints = SkiaWrapped.Matrix.mapPoints;
  let mapVectors = SkiaWrapped.Matrix.mapVectors;
  let mapXy = SkiaWrapped.Matrix.mapXy;
  let mapVector = SkiaWrapped.Matrix.mapVector;
  let mapRadius = SkiaWrapped.Matrix.mapRadius;

  let identity = makeAll(1., 0., 0., 0., 1., 0., 0., 0., 1.);
};

module Matrix44 = {
  type t = SkiaWrapped.Matrix44.t;

  let makeEmpty = () => {
    let mat = SkiaWrapped.Matrix44.allocate();
    Gc.finalise(SkiaWrapped.Matrix44.destroy, mat);
    mat;
  };

  let makeIdentity = () => {
    let mat = SkiaWrapped.Matrix44.allocate_identity();
    Gc.finalise(SkiaWrapped.Matrix44.destroy, mat);
    mat;
  };

  let get = SkiaWrapped.Matrix44.get;
  let set = SkiaWrapped.Matrix44.set;
  let setRotateAboutDegrees = SkiaWrapped.Matrix44.setRotateAboutDegrees;
  let setRotateAboutRadians = SkiaWrapped.Matrix44.setRotateAboutRadians;

  let setTranslate = SkiaWrapped.Matrix44.setTranslate;
  let preTranslate = SkiaWrapped.Matrix44.preTranslate;
  let postTranslate = SkiaWrapped.Matrix44.postTranslate;

  let setScale = SkiaWrapped.Matrix44.setScale;
  let preScale = SkiaWrapped.Matrix44.preScale;
  let postScale = SkiaWrapped.Matrix44.postScale;

  let setConcat = SkiaWrapped.Matrix44.setConcat;
  let preConcat = SkiaWrapped.Matrix44.preConcat;
  let postConcat = SkiaWrapped.Matrix44.postConcat;

  let toMatrix = SkiaWrapped.Matrix44.toMatrix;
};

module IRect = {
  type t = SkiaWrapped.IRect.t;

  let makeEmpty = SkiaWrapped.IRect.makeEmpty;
  let makeLtrb = SkiaWrapped.IRect.makeLtrb;
};

module Rect = {
  type t = SkiaWrapped.Rect.t;
  module CI = Cstubs_internals;

  module Mutable = {
    [@noalloc]
    external _set:
      (
        CI.fatptr(_),
        [@unboxed] float,
        [@unboxed] float,
        [@unboxed] float,
        [@unboxed] float
      ) =>
      unit =
      "reason_skia_rect_set_byte" "reason_skia_rect_set";

    let setLtrb = (~out, left, top, right, bottom) =>
      _set(CI.cptr(out), left, top, right, bottom);
  };

  [@noalloc]
  external _getLeft: CI.fatptr(_) => [@unboxed] float =
    "reason_skia_rect_get_left_byte" "reason_skia_rect_get_left";

  [@noalloc]
  external _getTop: CI.fatptr(_) => [@unboxed] float =
    "reason_skia_rect_get_top_byte" "reason_skia_rect_get_top";

  [@noalloc]
  external _getRight: CI.fatptr(_) => [@unboxed] float =
    "reason_skia_rect_get_right_byte" "reason_skia_rect_get_right";

  [@noalloc]
  external _getBottom: CI.fatptr(_) => [@unboxed] float =
    "reason_skia_rect_get_bottom_byte" "reason_skia_rect_get_bottom";

  let getLeft = rect => _getLeft(CI.cptr(rect));
  let getTop = rect => _getTop(CI.cptr(rect));
  let getBottom = rect => _getBottom(CI.cptr(rect));
  let getRight = rect => _getRight(CI.cptr(rect));

  let makeEmpty = SkiaWrapped.Rect.makeEmpty;
  let makeLtrb = SkiaWrapped.Rect.makeLtrb;

  let toString = rect => {
    let left = getLeft(rect);
    let right = getRight(rect);
    let top = getTop(rect);
    let bottom = getBottom(rect);

    Printf.sprintf(
      "Rect - left: %f top: %f right: %f bottom: %f",
      left,
      top,
      right,
      bottom,
    );
  };
};

module FontStyle = {
  type t = SkiaWrapped.FontStyle.t;
  type slant = SkiaWrapped.FontStyle.slant;

  let make = SkiaWrapped.FontStyle.make;
};

module Typeface = {
  type t = SkiaWrapped.Typeface.t;

  let makeFromName = SkiaWrapped.Typeface.makeFromName;
  let makeFromFile = SkiaWrapped.Typeface.makeFromFile;
};

module RRect = {
  type t = SkiaWrapped.RRect.t;
  type rRectType = SkiaWrapped.RRect.rRectType;
  type corner = SkiaWrapped.RRect.corner;

  let make = () => {
    let rRect = SkiaWrapped.RRect.allocate();
    Gc.finalise(SkiaWrapped.RRect.delete, rRect);
    rRect;
  };
  let copy = originalRRect => {
    let rRect = SkiaWrapped.RRect.allocateCopy(originalRRect);
    Gc.finalise(SkiaWrapped.RRect.delete, rRect);
    rRect;
  };

  let getType = SkiaWrapped.RRect.getType;
  let getRect = SkiaWrapped.RRect.getRect;
  let getRadii = SkiaWrapped.RRect.getRadii;
  let getWidth = SkiaWrapped.RRect.getWidth;
  let getHeight = SkiaWrapped.RRect.getHeight;
  let setEmpty = SkiaWrapped.RRect.setEmpty;
  let setRect = SkiaWrapped.RRect.setRect;
  let setOval = SkiaWrapped.RRect.setOval;
  let setRectXy = SkiaWrapped.RRect.setRectXy;
  let setNinePatch = SkiaWrapped.RRect.setNinePatch;
  let setRectRadii =
      (
        rRect,
        rect,
        topLeftRadii,
        topRightRadii,
        bottomRightRadii,
        bottomLeftRadii,
      ) => {
    let radiiCArray =
      Ctypes.CArray.make(SkiaWrappedBindings.SkiaTypes.Vector.t, 4);
    Ctypes.CArray.unsafe_set(radiiCArray, 0, Ctypes.(!@topLeftRadii));
    Ctypes.CArray.unsafe_set(radiiCArray, 1, Ctypes.(!@topRightRadii));
    Ctypes.CArray.unsafe_set(radiiCArray, 2, Ctypes.(!@bottomRightRadii));
    Ctypes.CArray.unsafe_set(radiiCArray, 3, Ctypes.(!@bottomLeftRadii));
    let radiiPointer = Ctypes.CArray.start(radiiCArray);
    SkiaWrapped.RRect.setRectRadii(rRect, rect, radiiPointer);
  };
  let inset = SkiaWrapped.RRect.inset;
  let outset = SkiaWrapped.RRect.outset;
  let offset = SkiaWrapped.RRect.offset;
  let contains = SkiaWrapped.RRect.contains;
  let isValid = SkiaWrapped.RRect.isValid;
  let transform = SkiaWrapped.RRect.transform;
};

module Path = {
  type t = SkiaWrapped.Path.t;
  type pathDirection = SkiaWrapped.Path.pathDirection;

  let make = () => {
    let path = SkiaWrapped.Path.allocate();
    Gc.finalise(SkiaWrapped.Path.delete, path);
    path;
  };

  let addCircle =
      (path, x, y, ~radius, ~direction: pathDirection=Clockwise, ()) =>
    SkiaWrapped.Path.addCircle(path, x, y, radius, direction);

  let addRoundRect =
      (path, rect, rx, ry, ~direction: pathDirection=Clockwise, ()) =>
    SkiaWrapped.Path.addRoundRect(path, rect, rx, ry, direction);

  let moveTo = SkiaWrapped.Path.moveTo;
  let lineTo = SkiaWrapped.Path.lineTo;
  let cubicTo = SkiaWrapped.Path.cubicTo;
  let close = SkiaWrapped.Path.close;
};

module ColorSpace = {
  type t = SkiaWrapped.ColorSpace.t;
};

module Data = {
  type t = SkiaWrapped.Data.t;

  let makeString = data => {
    let dataPtr =
      Ctypes.from_voidp(Ctypes.char, SkiaWrapped.Data.getData(data));
    let dataSize = Unsigned.Size_t.to_int(SkiaWrapped.Data.getSize(data));
    Ctypes.string_from_ptr(dataPtr, ~length=dataSize);
  };

  let makeFromFileName = path => {
    let data = SkiaWrapped.Data.makeFromFileName(path);
    Gc.finalise(SkiaWrapped.Data.delete, data);
    data;
  };
};

module ImageInfo = {
  type t = SkiaWrapped.ImageInfo.t;

  let make = SkiaWrapped.ImageInfo.make;
};

module Image = {
  type t =
    Ctypes_static.ptr(
      Ctypes.structure(SkiaWrappedBindings.SkiaTypes.Image.t),
    );

  let makeFromEncoded = (encodedData, subset) => {
    switch (SkiaWrapped.Image.allocateFromEncoded(encodedData, subset)) {
    | Some(image) =>
      Gc.finalise(SkiaWrapped.Image.delete, image);
      Some(image);
    | None => None
    };
  };

  let encodeToData = image => {
    let data = SkiaWrapped.Image.encode(image);
    Gc.finalise(SkiaWrapped.Data.delete, data);
    data;
  };
};

type pixelGeometry = SkiaWrapped.pixelGeometry;

module Gr = {
  type surfaceOrigin = SkiaWrapped.Gr.surfaceOrigin;

  module Gl = {
    module Interface = {
      type t = SkiaWrapped.Gr.Gl.Interface.t;

      let makeNative = SkiaWrapped.Gr.Gl.Interface.makeNative;
      let makeSdl2 = SkiaWrapped.Gr.Gl.Interface.makeSdl2;
    };

    module FramebufferInfo = {
      type t = SkiaWrapped.Gr.Gl.FramebufferInfo.t;

      let make = SkiaWrapped.Gr.Gl.FramebufferInfo.make;
    };
  };

  module Context = {
    type t = SkiaWrapped.Gr.Context.t;

    let makeGl = SkiaWrapped.Gr.Context.makeGl;
  };

  module BackendRenderTarget = {
    type t = SkiaWrapped.Gr.BackendRenderTarget.t;

    let makeGl = SkiaWrapped.Gr.BackendRenderTarget.makeGl;
  };
};

type clipOp = SkiaWrapped.clipOp;

module Canvas = {
  type t =
    Ctypes_static.ptr(
      Ctypes.structure(SkiaWrappedBindings.SkiaTypes.Canvas.t),
    );

  // TODO: Make fast
  let clear = (canvas, color) =>
    SkiaWrapped.Canvas.clear(canvas, Unsigned.UInt32.of_int32(color));

  let drawPaint = SkiaWrapped.Canvas.drawPaint;
  let drawRect = SkiaWrapped.Canvas.drawRect;
  let drawRectLtwh = SkiaWrapped.Canvas.drawRectLtwh;
  let drawRRect = SkiaWrapped.Canvas.drawRRect;
  let drawOval = SkiaWrapped.Canvas.drawOval;
  let drawPath = SkiaWrapped.Canvas.drawPath;
  let drawCircle = SkiaWrapped.Canvas.drawCircle;

  let drawText = (canvas, text, x, y, paint) => {
    SkiaWrapped.Canvas.drawText(
      canvas,
      text,
      String.length(text),
      x,
      y,
      paint,
    );
  };
  let drawImage = SkiaWrapped.Canvas.drawImage;
  let drawImageRect = SkiaWrapped.Canvas.drawImageRect;

  let concat = SkiaWrapped.Canvas.concat;
  let setMatrix = SkiaWrapped.Canvas.setMatrix;
  let translate = SkiaWrapped.Canvas.translate;
  let scale = SkiaWrapped.Canvas.scale;
  let rotate = SkiaWrapped.Canvas.rotate;
  let skew = SkiaWrapped.Canvas.skew;
  let resetMatrix = SkiaWrapped.Canvas.resetMatrix;

  let clipRect = SkiaWrapped.Canvas.clipRect;
  let clipPath = SkiaWrapped.Canvas.clipPath;
  let clipRRect = (canvas, rrect, clipOp: clipOp, antiAlias) => {
    SkiaWrapped.Canvas.clipRRect(canvas, rrect, clipOp, antiAlias);
  };

  let save = SkiaWrapped.Canvas.save;
  let saveLayer = SkiaWrapped.Canvas.saveLayer;
  let restore = SkiaWrapped.Canvas.restore;

  let flush = SkiaWrapped.Canvas.flush;
};

module SurfaceProps = {
  type t = SkiaWrapped.SurfaceProps.t;

  let make = SkiaWrapped.SurfaceProps.make;
};

module Surface = {
  type t =
    Ctypes_static.ptr(
      Ctypes.structure(SkiaWrappedBindings.SkiaTypes.Surface.t),
    );

  let makeRaster = (imageInfo, rowBytes, surfaceProps) => {
    let surface =
      SkiaWrapped.Surface.allocateRaster(
        imageInfo,
        Unsigned.Size_t.of_int(rowBytes),
        surfaceProps,
      );
    Gc.finalise(SkiaWrapped.Surface.delete, surface);
    surface;
  };
  let makeRenderTarget =
      (
        context,
        shouldBeBudgeted,
        imageInfo,
        sampleCount,
        surfaceOrigin,
        surfacePropsOption,
        shouldCreateWithMips,
      ) => {
    let surfaceOption =
      SkiaWrapped.Surface.allocateRenderTarget(
        context,
        shouldBeBudgeted,
        imageInfo,
        sampleCount,
        surfaceOrigin,
        surfacePropsOption,
        shouldCreateWithMips,
      );
    switch (surfaceOption) {
    | Some(surface) =>
      Gc.finalise(SkiaWrapped.Surface.delete, surface);
      Some(surface);
    | None => None
    };
  };
  let makeFromBackendRenderTarget =
      (
        context,
        backendRenderTarget,
        surfaceOrigin,
        colorType,
        colorSpaceOption,
        surfacePropsOption,
      ) => {
    let surfaceOption =
      SkiaWrapped.Surface.allocateFromBackendRenderTarget(
        context,
        backendRenderTarget,
        surfaceOrigin,
        colorType,
        colorSpaceOption,
        surfacePropsOption,
      );
    switch (surfaceOption) {
    | Some(surface) =>
      Gc.finalise(SkiaWrapped.Surface.delete, surface);
      Some(surface);
    | None => None
    };
  };

  let getCanvas = SkiaWrapped.Surface.getCanvas;
  let makeImageSnapshot = surface => {
    let imageSnapshot = SkiaWrapped.Surface.allocateImageSnapshot(surface);
    Gc.finalise(SkiaWrapped.Image.delete, imageSnapshot);
    imageSnapshot;
  };

  let getWidth = SkiaWrapped.Surface.getWidth;
  let getHeight = SkiaWrapped.Surface.getHeight;
  let getProps = SkiaWrapped.Surface.getProps;
};
