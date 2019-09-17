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
};

module Rect = {
    type t = SkiaWrapped.Rect.t;

    let makeEmpty = SkiaWrapped.Rect.makeEmpty;
    let makeLtrb = SkiaWrapped.Rect.makeLtrb;
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

module Colorspace = {
    type t = SkiaWrapped.Colorspace.t;
};

module Data = {
    type t = SkiaWrapped.Data.t;

    let makeString = data => {
        let dataPtr = Ctypes.from_voidp(Ctypes.char, SkiaWrapped.Data.getData(data));
        let dataSize = Unsigned.Size_t.to_int(SkiaWrapped.Data.getSize(data));
        Ctypes.string_from_ptr(dataPtr, ~length=dataSize);
    };
};

module Imageinfo = {
    type t = SkiaWrapped.Imageinfo.t;

    let make = SkiaWrapped.Imageinfo.make;
};

module Image = {
    type t = SkiaWrapped.Image.t;

    let encodeToData = image => {
        let data = SkiaWrapped.Image.encode(image);
        Gc.finalise(SkiaWrapped.Data.delete, data);
        data;
    };
};

module Canvas = {
    type t = SkiaWrapped.Canvas.t;

    let drawPaint = SkiaWrapped.Canvas.drawPaint;
    let drawRect = SkiaWrapped.Canvas.drawRect;
    let drawOval = SkiaWrapped.Canvas.drawOval;
    let drawPath = SkiaWrapped.Canvas.drawPath;
};   

module SurfaceProps = {
    type t = SkiaWrapped.SurfaceProps.t;
};

module Surface = {
    type t = SkiaWrapped.Surface.t;

    let makeRaster = (imageinfo, rowBytes, surfaceProps) => {
        let surface = SkiaWrapped.Surface.allocateRaster(
            imageinfo,
            Unsigned.Size_t.of_int(rowBytes),
            surfaceProps,
        );
        Gc.finalise(SkiaWrapped.Surface.delete, surface);
        surface;
    };

    let getCanvas = SkiaWrapped.Surface.getCanvas;
    let makeImageSnapshot = surface => {
        let imageSnapshot = SkiaWrapped.Surface.allocateImageSnapshot(surface);
        Gc.finalise(SkiaWrapped.Image.delete, imageSnapshot);
        imageSnapshot;
    };
};
