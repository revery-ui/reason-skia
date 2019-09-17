open Skia;

let makeSurface = (width, height) => {
    let imageinfo = Imageinfo.make(width, height, Rgba8888, Premul, None);
    Surface.makeRaster(imageinfo, 0, None);
};

let emitPng = (path, surface) => {
    let image = Surface.makeImageSnapshot(surface);
    let data = Image.encodeToData(image);
    let dataString = Data.makeString(data);
    let fileOutputChannel = open_out_bin(path);
    output_string(fileOutputChannel, dataString);
    close_out(fileOutputChannel);
};

let draw = (canvas) => {
    let fill = Paint.make();
    Paint.setColor(fill, Color.makeArgb(0xFF, 0x00, 0x00, 0xFF));
    Canvas.drawPaint(canvas, fill);

    Paint.setColor(fill, Color.makeArgb(0xFF, 0x00, 0xFF, 0xFF));
    let rect = Rect.makeLtrb(100., 100., 540., 380.);
    Canvas.drawRect(canvas, rect, fill);

    let stroke = Paint.make();
    Paint.setColor(stroke, Color.makeArgb(0xFF, 0xFF, 0x00, 0x00));
    Paint.setAntiAlias(stroke, true);
    Paint.setStyle(stroke, Stroke);
    Paint.setStrokeWidth(stroke, 5.);

    let path = Path.make();
    Path.moveTo(path, 50., 50.);
    Path.lineTo(path, 590., 50.);
    Path.cubicTo(path, -490., 50., 1130., 430., 50., 430.);
    Path.lineTo(path, 590., 430.);
    Canvas.drawPath(canvas, path, stroke);

    Paint.setColor(fill, Color.makeArgb(0x80, 0x00, 0xFF, 0x00));
    let rect2 = Rect.makeLtrb(120., 120., 520., 360.);
    Canvas.drawOval(canvas, rect2, fill);
};

let surface = makeSurface(640l, 480l);
let canvas = Surface.getCanvas(surface);
draw(canvas);
emitPng("skia-c-example.png", surface);
