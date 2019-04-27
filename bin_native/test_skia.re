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

let ovalColor = Sk.Color.make(60, 130, 0, 80);
let ovalPaint = Sk.Paint.make();
Sk.Paint.setColor(ovalPaint, ovalColor);
let ovalRRect = Sk.RRect.makeOval(Sk.Rect.makeXYWH(300., 70., 120., 230.));
Sk.Canvas.drawRRect(canvas, ovalRRect, ovalPaint);

let roundedBoxColor = Sk.Color.make(100, 30, 30, 80);
let roundedBoxPaint = Sk.Paint.make();
Sk.Paint.setColor(roundedBoxPaint, roundedBoxColor);
let roundedBoxRRect =
  Sk.RRect.makeRectXY(Sk.Rect.makeXYWH(500., 470., 120., 230.), 20., 30.);
Sk.Canvas.drawRRect(canvas, roundedBoxRRect, roundedBoxPaint);

let complexRoundedThingColor = Sk.Color.make(255, 255, 255, 255);
let complexRoundedThingPaint = Sk.Paint.make();
Sk.Paint.setColor(complexRoundedThingPaint, complexRoundedThingColor);
let complexRoundedThingRect = Sk.Rect.makeXYWH(120., 300., 200., 200.);
let complexRoundedThingRRect = Sk.RRect.makeRect(complexRoundedThingRect);
Sk.RRect.setRectRadii(
  complexRoundedThingRRect,
  complexRoundedThingRect,
  ((15., 30.), (10., 40.), (0., 10.), (100., 50.)),
);
Sk.Canvas.drawRRect(
  canvas,
  complexRoundedThingRRect,
  complexRoundedThingPaint,
);

let image = Sk.Surface.makeImageSnapshot(surface);
let png = Sk.Image.encodeToData(image);
let outputStream =
  Sk.FILEWStream.make(getExecutingDirectory() ++ "testImage.png");
Sk.FILEWStream.write(outputStream, png);