open Skia;

let getExecutingDirectory = () =>
  Filename.dirname(Sys.argv[0]) ++ Filename.dir_sep;

let imageInfo = Sk.ImageInfo.make(800, 600, N32, Premul, None);
let surface = Sk.Surface.makeRaster(imageInfo);
let canvas = Sk.Surface.getCanvas(surface);

let bgColor = Sk.Color.make(255, 100, 0, 200);
let bgPaint = Sk.Paint.make();
Sk.Paint.setColor(bgPaint, bgColor);
Sk.Canvas.drawPaint(canvas, bgPaint);

let boxColor = Sk.Color.make(255, 30, 220, 80);
let boxPaint = Sk.Paint.make();
Sk.Paint.setColor(boxPaint, boxColor);
let boxRect = Sk.Rect.makeXYWH(230., 170., 440., 280.);
Sk.Canvas.drawRect(canvas, boxRect, boxPaint);

let image = Sk.Surface.makeImageSnapshot(surface);
let png = Sk.Image.encodeToData(image);
let outputStream =
  Sk.FILEWStream.make(getExecutingDirectory() ++ "testImage.png");
Sk.FILEWStream.write(outputStream, png);