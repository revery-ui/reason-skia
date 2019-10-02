type colorType = SkiaWrapped.colorType;
type alphaType = SkiaWrapped.alphaType;

module Color = {
    type t = SkiaWrapped.Color.t;

    let makeArgb = SkiaWrapped.Color.makeArgb;
};

module Paint = {
    type t = SkiaWrapped.Paint.t;
    type style = SkiaWrapped.Paint.style;

    let make = () => {
      let paint = SkiaWrapped.Paint.allocate();
      Gc.finalise(SkiaWrapped.Paint.delete, paint);
      paint;
    };

    let setColor = SkiaWrapped.Paint.setColor;
    let setAntiAlias = SkiaWrapped.Paint.setAntiAlias;
    let setStyle = SkiaWrapped.Paint.setStyle;
    let setStrokeWidth = SkiaWrapped.Paint.setStrokeWidth;
    let setLcdRenderText = SkiaWrapped.Paint.setLcdRenderText;
    let setTextSize = SkiaWrapped.Paint.setTextSize;
    let setTypeFace = SkiaWrapped.Paint.setTypeFace;
};

module Matrix = {
    type t = SkiaWrapped.Matrix.t;

    let make = SkiaWrapped.Matrix.make;
    let setAll = SkiaWrapped.Matrix.setAll;
    let get = SkiaWrapped.Matrix.get;
    let set = SkiaWrapped.Matrix.set;

    let setTranslate = (matrix, translateX, translateY) =>
      setAll(
        matrix,
        1., 0., translateX,
        0., 1., translateY,
        0., 0., 1.,
      );
    let setScale = (matrix, scaleX, scaleY, pivotX, pivotY) =>
      setAll(
        matrix,
        scaleX, 0.,     pivotX -. scaleX *. pivotX,
        0.,     scaleY, pivotY -. scaleY *. pivotY,
        0.,     0.,     1.,
      );

    let makeAll = (
      scaleX, skewX, translateX,
      skewY, scaleY, translateY,
      perspective0, perspective1, perspective2
    ) => {
      let matrix = make();
      setAll(
        matrix,
        scaleX, skewX, translateX,
        skewY, scaleY, translateY,
        perspective0, perspective1, perspective2
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
    
    let getScaleX = (matrix) => get(matrix,0);
    let getScaleY = (matrix) => get(matrix, 4);
    let getSkewX = (matrix) => get(matrix, 1);
    let getSkewY = (matrix) => get(matrix, 3);
    let getTranslateX = (matrix) => get(matrix, 2);
    let getTranslateY = (matrix) => get(matrix, 5);
    let getPerspX = (matrix) => get(matrix, 6);
    let getPerspY = (matrix) => get(matrix, 7);

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
        1.,     skewX,  -.skewX *. pivotY,
        skewY,  1.,     -.skewY *. pivotX,
        0.,     0.,     1.,
      );
    let setIdentity = (matrix) =>
        setAll(
            matrix,
            1., 0., 0.,
            0., 1., 0.,
            0., 0., 1.,
        );
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

    let identity = makeAll(
      1., 0., 0.,
      0., 1., 0.,
      0., 0., 1.,
    );
};


module Matrix44 = {
    type t = SkiaWrapped.Matrix44.t;

    let make = () => {
        let mat = SkiaWrapped.Matrix44.make();
        Gc.finalise(SkiaWrapped.Matrix44.destroy, mat);
        mat;
    };

    let get = SkiaWrapped.Matrix44.get;
    let set = SkiaWrapped.Matrix44.set;
    let toMatrix = SkiaWrapped.Matrix44.toMatrix;
};

module IRect = {
    type t = SkiaWrapped.IRect.t;

    let makeEmpty = SkiaWrapped.IRect.makeEmpty;
    let makeLtrb = SkiaWrapped.IRect.makeLtrb;
};

module Rect = {
    type t = SkiaWrapped.Rect.t;

    let makeEmpty = SkiaWrapped.Rect.makeEmpty;
    let makeLtrb = SkiaWrapped.Rect.makeLtrb;
};

module FontStyle = {
    type t = SkiaWrapped.FontStyle.t;
    
    let newFontStyle = SkiaWrapped.FontStyle.newFontStyle;
};

module TypeFace = {
    type t = Ctypes_static.ptr(Ctypes.structure(SkiaWrappedBindings.SkiaTypes.TypeFace.t));

    let createFromNameWithFontStyle = SkiaWrapped.TypeFace.createFromNameWithFontStyle;
    let createFromFile = SkiaWrapped.TypeFace.createFromFile;
}

module RRect = {
    type t = SkiaWrapped.RRect.t;
    type rrectType = SkiaWrapped.RRect.rrectType;
    type corner = SkiaWrapped.RRect.corner;

    let make = () => {
        let rRect = SkiaWrapped.RRect.allocate();
        Gc.finalise(SkiaWrapped.RRect.delete, rRect);
        rRect;
    };
    let copy = (originalRRect) => {
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
    let setRectRadii = SkiaWrapped.RRect.setRectRadii;
    let inset = SkiaWrapped.RRect.inset;
    let outset = SkiaWrapped.RRect.outset;
    let offset = SkiaWrapped.RRect.offset;
    let contains = SkiaWrapped.RRect.contains;
    let isValid = SkiaWrapped.RRect.isValid;
    let transform = SkiaWrapped.RRect.transform;
};

module Path = {
    type t = SkiaWrapped.Path.t;

    let make = () => {
      let path = SkiaWrapped.Path.allocate();
      Gc.finalise(SkiaWrapped.Path.delete, path);
      path;
    };

    let moveTo = SkiaWrapped.Path.moveTo;
    let lineTo = SkiaWrapped.Path.lineTo;
    let cubicTo = SkiaWrapped.Path.cubicTo;
};

module ColorSpace = {
    type t = SkiaWrapped.ColorSpace.t;
};

module Data = {
    type t = SkiaWrapped.Data.t;

    let makeString = data => {
        let dataPtr = Ctypes.from_voidp(Ctypes.char, SkiaWrapped.Data.getData(data));
        let dataSize = Unsigned.Size_t.to_int(SkiaWrapped.Data.getSize(data));
        Ctypes.string_from_ptr(dataPtr, ~length=dataSize);
    };

    let newFromFile = (path) => {
        let data = SkiaWrapped.Data.newFromFile(path);
        Gc.finalise(SkiaWrapped.Data.delete, data);
        data;
    };
};

module ImageInfo = {
    type t = SkiaWrapped.ImageInfo.t;

    let make = SkiaWrapped.ImageInfo.make;
};

module Image = {
    type t = Ctypes_static.ptr(Ctypes.structure(SkiaWrappedBindings.SkiaTypes.Image.t));

    let makeFromEncoded = (encodedData, subset) => {
        switch(SkiaWrapped.Image.allocateFromEncoded(encodedData, subset)) {
            | Some(image) => {
                Gc.finalise(SkiaWrapped.Image.delete, image);
                Some(image);
            }
            | None => None;
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
        

module Canvas = {
    type t = Ctypes_static.ptr(Ctypes.structure(SkiaWrappedBindings.SkiaTypes.Canvas.t));

    let drawImage = SkiaWrapped.Canvas.drawImage;
    let drawPaint = SkiaWrapped.Canvas.drawPaint;
    let drawRect = SkiaWrapped.Canvas.drawRect;
    let drawOval = SkiaWrapped.Canvas.drawOval;
    let drawPath = SkiaWrapped.Canvas.drawPath;

    let drawText = (canvas, text, x, y, paint) => {
        SkiaWrapped.Canvas.drawText(canvas, text, String.length(text), x, y, paint);
    };
    let flush = SkiaWrapped.Canvas.flush;
    let restore = SkiaWrapped.Canvas.restore;
    let save = SkiaWrapped.Canvas.save;
    let translate = SkiaWrapped.Canvas.translate;

    let setMatrix = SkiaWrapped.Canvas.setMatrix;
};   

module SurfaceProps = {
    type t = SkiaWrapped.SurfaceProps.t;

    let make = SkiaWrapped.SurfaceProps.make;
};

module Surface = {
    type t = Ctypes_static.ptr(Ctypes.structure(SkiaWrappedBindings.SkiaTypes.Surface.t));

    let makeRaster = (imageinfo, rowBytes, surfaceProps) => {
        let surface = SkiaWrapped.Surface.allocateRaster(
            imageinfo,
            Unsigned.Size_t.of_int(rowBytes),
            surfaceProps,
        );
        Gc.finalise(SkiaWrapped.Surface.delete, surface);
        surface;
    };
    let makeRenderTarget = (context, shouldBeBudgeted, imageinfo, sampleCount, colorType, colorSpace, surfaceProps) => {
        let surfaceOption =
            SkiaWrapped.Surface.allocateRenderTarget(
                context,
                shouldBeBudgeted,
                imageinfo,
                sampleCount,
                colorType,
                colorSpace,
                surfaceProps
            );
        switch (surfaceOption) {
        | Some(surface) => {
            Gc.finalise(SkiaWrapped.Surface.delete, surface);
            Some(surface);
        }
        | None => None;
        };
    };
    let makeFromBackendRenderTarget = (context, backendRenderTarget, surfaceOrigin, colorType, colorSpace, surfaceProps) => {
        let surfaceOption =
            SkiaWrapped.Surface.allocateFromBackendRenderTarget(
                context,
                backendRenderTarget,
                surfaceOrigin,
                colorType,
                colorSpace,
                surfaceProps
            );
        switch (surfaceOption) {
        | Some(surface) => {
            Gc.finalise(SkiaWrapped.Surface.delete, surface);
            Some(surface);
        }
        | None => None;
        };
    };

    let getCanvas = SkiaWrapped.Surface.getCanvas;
    let makeImageSnapshot = surface => {
        let imageSnapshot = SkiaWrapped.Surface.allocateImageSnapshot(surface);
        Gc.finalise(SkiaWrapped.Image.delete, imageSnapshot);
        imageSnapshot;
    };
};
