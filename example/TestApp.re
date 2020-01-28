open Skia;

let makeSurface = (width, height) => {
  let imageInfo = ImageInfo.make(width, height, Rgba8888, Premul, None);
  Surface.makeRaster(imageInfo, 0, None);
};

// TODO we will need additional tools for setting up an OpenGL context for this to work.
// See /tools/gpu inside the skia codebase
//
// let makeGpuSurface = (width, height) => {
//     let glInterfaceOption = Gr.Gl.Interface.makeNative();
//     if (glInterfaceOption === None) {
//         print_endline("GL Interface Creation failed");
//     }
//     let glContextOption = Gr.Context.makeGl(glInterfaceOption);
//     switch (glContextOption) {
//     | None => {
//         print_endline("GL Context creation failed");
//         None;
//     }
//     | Some(glContext) => {
//         // TODO the following should be made more idiomatic
//         let framebufferInfo = Gr.Gl.FramebufferInfo.make(Unsigned.UInt.of_int(0), Unsigned.UInt.of_int(0x8058)); // GR_GL_RGBA8
//         let backendRenderTarget = Gr.BackendRenderTarget.makeGl(width, height, 0, 8, Some(framebufferInfo));
//         let surfaceProps = SurfaceProps.make(Unsigned.UInt32.of_int(0), Unknown);
//         Surface.makeFromBackendRenderTarget(glContext, backendRenderTarget, TopLeft, Rgba8888, None, Some(surfaceProps));
//     }
//     };
// };

let emitPng = (path, surface) => {
  let image = Surface.makeImageSnapshot(surface);
  let data = Image.encodeToData(image);
  let dataString = Data.makeString(data);
  let fileOutputChannel = open_out_bin(path);
  output_string(fileOutputChannel, dataString);
  close_out(fileOutputChannel);
};

let draw = canvas => {
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

  Paint.setColor(fill, Color.makeArgb(0xCC, 0x00, 0xFF, 0x00));
  Paint.setImageFilter(
    fill,
    ImageFilter.makeDropShadow(
      10.,
      10.,
      3.,
      3.,
      Color.makeArgb(0xAA, 0x00, 0x00, 0x00),
      DrawShadowAndForeground,
      None,
      None,
    ),
  );
  let rect2 = Rect.makeLtrb(120., 120., 520., 360.);
  Canvas.drawOval(canvas, rect2, fill);

  let fill3 = Paint.make();
  Paint.setColor(fill3, Color.makeArgb(0xFF, 0xFF, 0xFF, 0xFF));
  Paint.setTextSize(fill3, 30.);

  let nonExistentTypeface = Typeface.makeFromFile("non-existent-font.ttf", 0);
  assert(nonExistentTypeface == None);

  // Draw text
  let filePath = Sys.getcwd() ++ "/example/Orbitron Medium.ttf";
  print_endline("Loading font: " ++ filePath);
  let maybeTypeface = Typeface.makeFromFile(filePath, 0);
  switch (maybeTypeface) {
  | None => failwith("Unable to load font: " ++ filePath)
  | Some(typeFace) =>
    print_endline(__LOC__ ++ ": we will set.");
    Paint.setTypeface(fill3, typeFace);
    print_endline(__LOC__ ++ ": setTypeface is OK.");
    Canvas.drawText(canvas, "Hello, world!", 30., 30., fill3);
    let metrics = FontMetrics.make();
    let _ret: float = Paint.getFontMetrics(fill3, metrics, 1.0);

    print_endline(
      "-- Top: " ++ string_of_float(FontMetrics.getTop(metrics)),
    );
    print_endline(
      "-- Bottom: " ++ string_of_float(FontMetrics.getBottom(metrics)),
    );
    print_endline("-- Ret: " ++ string_of_float(_ret));

    print_endline(__LOC__ ++ ": We return.");
  };

  // Load and draw image
  let imgPath = Sys.getcwd() ++ "/assets/uv.png";
  print_endline("Loading image: " ++ imgPath);
  let imgData = Data.makeFromFileName(imgPath);
  let strLen = String.length(Data.makeString(imgData));
  print_endline("Bytes loaded: " ++ string_of_int(strLen));
  let maybeImg = Image.makeFromEncoded(imgData, None);

  switch (maybeImg) {
  | None => failwith("Unable to load image: uv.png")
  | Some(img) =>
    let imgFill = Paint.make();
    Canvas.drawImage(canvas, img, 250., 250., Some(imgFill));

    let sourceRect = Rect.makeLtrb(0., 0., 128., 128.);
    let destRect = Rect.makeLtrb(200., 200., 264., 264.);
    Canvas.drawImageRect(
      canvas,
      img,
      Some(sourceRect),
      destRect,
      Some(imgFill),
    );
  };

  // Draw text w/ ligature
  let filePath = Sys.getcwd() ++ "/example/FiraCode-Regular.ttf";
  print_endline("Loading font: " ++ filePath);
  let maybeTypeface = Typeface.makeFromFile(filePath, 0);
  switch (maybeTypeface) {
  | None => failwith("Unable to load font: " ++ filePath)
  | Some(typeFace) =>
    let fill = Paint.make();
    Paint.setColor(fill, Color.makeArgb(0xFF, 0xFF, 0xFF, 0xFF));
    Paint.setTextSize(fill, 30.);
    Paint.setTypeface(fill, typeFace);
    Paint.setTextEncoding(fill, GlyphId);

    let glyphsToString = glyphs => {
      let len = List.length(glyphs);
      let bytes = Bytes.create(len * 2);

      let rec loop = (glyphs, idx) => {
        switch (glyphs) {
        | [hd, ...tail] =>
          let lowerBit = hd land 255;
          let highBit = (hd land 255 lsl 8) lsr 8;
          Bytes.set(bytes, idx * 2 + 0, Char.chr(lowerBit));
          Bytes.set(bytes, idx * 2 + 1, Char.chr(highBit));
          loop(tail, idx + 1);
        | [] => ()
        };
      };

      loop(glyphs, 0);

      Bytes.to_string(bytes);
    };

    // For FiraCode, this is a==>b
    let str = glyphsToString([136, 1624, 1624, 1495, 148]);
    Canvas.drawText(canvas, str, 50., 100., fill);
  };
};

let surface = makeSurface(640l, 480l);
let canvas = Surface.getCanvas(surface);
draw(canvas);
emitPng("skia-c-example.png", surface);

// let surfaceOption = makeGpuSurface(640, 480);
// switch (surfaceOption) {
// | Some(surface) => {
//     let canvas = Surface.getCanvas(surface);
//     draw(canvas);
//     emitPng("skia-gpu-c-example.png", surface);
// }
// | None => print_endline("Surface creation failed")
// };
