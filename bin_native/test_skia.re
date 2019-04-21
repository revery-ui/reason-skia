open Skia;

let getExecutingDirectory = () =>
  Filename.dirname(Sys.argv[0]) ++ Filename.dir_sep;

let imageInfo = Sk.ImageInfo.make(800, 600, N32, Premul, None);
let gpuSurface = Sk.Surface.makeRaster(imageInfo);
let gpuCanvas = Sk.Surface.getCanvas(gpuSurface);
let color = Sk.Color.make(255, 100, 0, 200);
let paint = Sk.Paint.make();
Sk.Paint.setColor(paint, color);
Sk.Canvas.drawPaint(gpuCanvas, paint);
let image = Sk.Surface.makeImageSnapshot(gpuSurface);
let png = Sk.Image.encodeToData(image);
let outputStream =
  Sk.FILEWStream.make(getExecutingDirectory() ++ "testImage.png");
Sk.FILEWStream.write(outputStream, png);