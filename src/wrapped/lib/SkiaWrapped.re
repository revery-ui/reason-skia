module SkiaBindings = SkiaWrappedBindings.M(Skia_wrapped_generated_stubs);

module Color = {
    type t = SkiaBindings.Color.t;

    let makeArgb = SkiaBindings.Color.makeArgb;
};

module Paint = {
    type t = SkiaBindings.Paint.t;
    type style = SkiaBindings.Paint.style;

    let make = () => {
      let paint = SkiaBindings.Paint.allocate();
      Gc.finalise(SkiaBindings.Paint.delete, paint);
      paint;
    };

    let setColor = SkiaBindings.Paint.setColor;
    let setAntiAlias = SkiaBindings.Paint.setAntiAlias;
    let setStyle = SkiaBindings.Paint.setStyle;
    let setStrokeWidth = SkiaBindings.Paint.setStrokeWidth;
};

module Rect = {
    type t = SkiaBindings.Rect.t;

    let makeEmpty = SkiaBindings.Rect.makeEmpty;
    let makeLtrb = SkiaBindings.Rect.makeLtrb;
};

module Path = {
    type t = SkiaBindings.Path.t;

    let make = () => {
      let path = SkiaBindings.Path.allocate();
      Gc.finalise(SkiaBindings.Path.delete, path);
      path;
    };

    let moveTo = SkiaBindings.Path.moveTo;
    let lineTo = SkiaBindings.Path.lineTo;
    let cubicTo = SkiaBindings.Path.cubicTo;
};

module Data = {
    type t = SkiaBindings.Data.t;

    let makeString = data => {
        let dataPtr = Ctypes.from_voidp(Ctypes.char, SkiaBindings.Data.getData(data));
        let dataSize = Unsigned.Size_t.to_int(SkiaBindings.Data.getSize(data));
        Ctypes.string_from_ptr(dataPtr, dataSize);
    };
};

module Imageinfo = {
    type t = SkiaBindings.Imageinfo.t;

    let make = SkiaBindings.Imageinfo.make;
};

module Image = {
    type t = SkiaBindings.Image.t;

    let encodeToData = image => {
        let data = SkiaBindings.Image.encode(image);
        Gc.finalise(SkiaBindings.Data.delete, data);
        data;
    };
};

module Canvas = {
    type t = SkiaBindings.Canvas.t;

    let drawPaint = SkiaBindings.Canvas.drawPaint;
    let drawRect = SkiaBindings.Canvas.drawRect;
    let drawOval = SkiaBindings.Canvas.drawOval;
    let drawPath = SkiaBindings.Canvas.drawPath;
};   

module SurfaceProps = {
    type t = SkiaBindings.SurfaceProps.t;
};

module Surface = {
    type t = SkiaBindings.Surface.t;

    let makeRaster = (imageinfo, rowBytes, surfaceProps) => {
        let surface = SkiaBindings.Surface.allocateRaster(
            imageinfo,
            Unsigned.Size_t.of_int(rowBytes),
            surfaceProps,
        );
        Gc.finalise(SkiaBindings.Surface.delete, surface);
        surface;
    };

    let getCanvas = SkiaBindings.Surface.getCanvas;
    let makeImageSnapshot = surface => {
        let imageSnapshot = SkiaBindings.Surface.allocateImageSnapshot(surface);
        Gc.finalise(SkiaBindings.Image.delete, imageSnapshot);
        imageSnapshot;
    };
};