type colorType = SkiaWrapped.colorType;
type alphaType = SkiaWrapped.alphaType;

module Color: {
    type t;
    
    let makeArgb: (int, int, int, int) => t;
};

module Paint: {
    type t;
    type style = SkiaWrapped.Paint.style;

    let make: unit => t;
    
    let setColor: (t, Color.t) => unit;
    let setAntiAlias: (t, bool) => unit;
    let setStyle: (t, style) => unit;
    let setStrokeWidth: (t, float) => unit;
};

module Rect: {
    type t;

    let makeEmpty: unit => t;
    let makeLtrb: (float, float, float, float) => t;
};

module Colorspace: {
    type t;
};

module Path: {
    type t;

    let make: unit => t;

    let moveTo: (t, float, float) => unit;
    let lineTo: (t, float, float) => unit;
    let cubicTo: (t, float, float) => unit;
};   

module Data: {
    type t;

    let makeString: t => string;
};

module Imageinfo: {
    type t;

    let make: (int32, int32, colorType, alphaType, option(Colorspace.t)) => t;
};

module Image: {
    type t;

    let encodeToData: t => Data.t;
};

module Canvas: {
    type t;

    let drawPaint: (t, Paint.t) => unit;
    let drawRect: (t, Rect.t) => unit;
    let drawOval: (t, Rect.t) => unit;
    let drawPath: (t, Path.t) => unit;
};

module SurfaceProps: {
    type t;
};

module Surface: {
    type t;

    let makeRaster: (Imageinfo.t, int, option(SurfaceProps.t)) => t;

    let makeImageSnapshot: t => Image.t;
};