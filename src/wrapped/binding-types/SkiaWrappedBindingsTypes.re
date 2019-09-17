open Ctypes;

module M = (T: TYPE) => {
  open T;

  let skiaCEnum = (name, mapping) => enum(
    name,
    ~typedef=true,
    List.map(((constructor, constantName)) => (constructor, constant(constantName, int64_t)), mapping),
    ~unexpected = i => invalid_arg(Printf.sprintf("Unsupported %s enum: %Ld", name, i)),
  );

  module Paint = {
    type t;
    let t: typ(structure(t)) = structure("sk_paint_t");
    let t = typedef(t, "sk_paint_t");
 
    type style =
      | Fill
      | Stroke
      | StrokeAndFill;
    let style = skiaCEnum(
      "sk_paint_style_t",
      [
        (Fill, "FILL_SK_PAINT_STYLE"),
        (Stroke, "STROKE_SK_PAINT_STYLE"),
        (StrokeAndFill, "STROKE_AND_FILL_SK_PAINT_STYLE"),
      ],
    );
  };

  module Rect = {
    type t;
    let t: typ(structure(t)) = structure("sk_rect_t");
    let left = field(t, "left", float);
    let top = field(t, "top", float);
    let right = field(t, "right", float);
    let bottom = field(t, "bottom", float);
    seal(t);
    let t = typedef(t, "sk_rect_t");
  };

  module Path = {
    type t;
    let t: typ(structure(t)) = structure("sk_path_t");
    let t = typedef(t, "sk_path_t");
  };
  
  module Colorspace = {
    type t;
    let t: typ(structure(t)) = structure("sk_colorspace_t");
    let t = typedef(t, "sk_colorspace_t");
  };

  type colorType =
    | Unknown
    | Alpha8
    | Rgb565
    | Argb4444
    | Rgba8888
    | Rgb888x
    | Bgra8888
    | Rgba1010102
    | Rgb101010x
    | Gray8
    | RgbaF16;
  let colorType = enum(
    "sk_colortype_t",
    ~typedef=true,
    [
      (Unknown, constant("UNKNOWN_SK_COLORTYPE", int64_t)),
      (Alpha8, constant("ALPHA_8_SK_COLORTYPE", int64_t)),
      (Rgb565, constant("RGB_565_SK_COLORTYPE", int64_t)),
      (Argb4444, constant("ARGB_4444_SK_COLORTYPE", int64_t)),
      (Rgba8888, constant("RGBA_8888_SK_COLORTYPE", int64_t)),
      (Rgb888x, constant("RGB_888X_SK_COLORTYPE", int64_t)),
      (Bgra8888, constant("BGRA_8888_SK_COLORTYPE", int64_t)),
      (Rgba1010102, constant("RGBA_1010102_SK_COLORTYPE", int64_t)),
      (Rgb101010x, constant("RGB_101010X_SK_COLORTYPE", int64_t)),
      (Gray8, constant("GRAY_8_SK_COLORTYPE", int64_t)),
      (RgbaF16, constant("RGBA_F16_SK_COLORTYPE", int64_t)),
    ],
    ~unexpected = i => invalid_arg(Printf.sprintf("Unsupported colortype enum: %Ld", i)),
  );

  type alphaType =
    | Unknown
    | Opaque
    | Premul
    | Unpremul;
  let alphaType = enum(
    "sk_alphatype_t",
    ~typedef=true,
    [
      (Unknown, constant("UNKNOWN_SK_ALPHATYPE", int64_t)),
      (Opaque, constant("OPAQUE_SK_ALPHATYPE", int64_t)),
      (Premul, constant("PREMUL_SK_ALPHATYPE", int64_t)),
      (Unpremul, constant("UNPREMUL_SK_ALPHATYPE", int64_t)),
    ],
    ~unexpected = i => invalid_arg(Printf.sprintf("Unsupported alphatype enum: %Ld", i)),
  );

  module Data = {
    type t;
    let t: typ(structure(t)) = structure("sk_data_t");
    let t = typedef(t, "sk_data_t");
  };

  module Imageinfo = {
    type t;
    let t: typ(structure(t)) = structure("sk_imageinfo_t");
    let colorspace = field(t, "colorspace", ptr_opt(Colorspace.t));
    let width = field(t, "width", int32_t);
    let height = field(t, "height", int32_t);
    let colorType = field(t, "colorType", colorType);
    let alphaType = field(t, "alphaType", alphaType);
    seal(t);
    let t = typedef(t, "sk_imageinfo_t");
  };

  module Image = {
    type t;
    let t: typ(structure(t)) = structure("sk_image_t");
    let t = typedef(t, "sk_image_t");
  };

  module Canvas = {
    type t;
    let t: typ(structure(t)) = structure("sk_canvas_t");
    let t = typedef(t, "sk_canvas_t");
  };

  module SurfaceProps = {
    type t;
    let t: typ(structure(t)) = structure("sk_surfaceprops_t");
    let t = typedef(t, "sk_surfaceprops_t");
  };

  module Surface = {
    type t;
    let t: typ(structure(t)) = structure("sk_surface_t");
    let t = typedef(t, "sk_surface_t");
  };
};
