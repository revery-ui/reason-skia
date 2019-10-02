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

  module Point = {
    type t;
    let t: typ(structure(t)) = structure("sk_point_t");
    let x = field(t, "x", float);
    let y = field(t, "y", float);
    seal(t);
    let t = typedef(t, "sk_point_t");
  };

  module Vector = {
    type t = Point.t;
    let t = Point.t;
  };

  module Matrix = {
    type t;
    let t: typ(structure(t)) = structure("sk_matrix_t");
    let mat = field(t, "mat", array(9, float));
    seal(t);
    let t = typedef(t, "sk_matrix_t");
  };

  module Matrix44 = {
    type t;
    let t: typ(structure(t)) = structure("sk_matrix44_t");
    let t = typedef(t, "sk_matrix44_t");
  };

  module IRect = {
    type t;
    let t: typ(structure(t)) = structure("sk_irect_t");
    let left = field(t, "left", int32_t);
    let top = field(t, "top", int32_t);
    let right = field(t, "right", int32_t);
    let bottom = field(t, "bottom", int32_t);
    seal(t);
    let t = typedef(t, "sk_irect_t");
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

  module RRect = {
    type t;
    let t: typ(structure(t)) = structure("sk_rrect_t");
    let t = typedef(t, "sk_rrect_t");

    // this should be called "type" only but that's a reserved keyword
    type rrectType =
      | Empty
      | Rect
      | Oval
      | Simple
      | NinePatch
      | Complex;
    let rrectType = skiaCEnum(
      "sk_rrect_type_t",
      [
        (Empty, "EMPTY_SK_RRECT_TYPE"),
        (Rect, "RECT_SK_RRECT_TYPE"),
        (Oval, "OVAL_SK_RRECT_TYPE"),
        (Simple, "SIMPLE_SK_RRECT_TYPE"),
        (NinePatch, "NINE_PATCH_SK_RRECT_TYPE"),
        (Complex, "COMPLEX_SK_RRECT_TYPE"),
      ],
    );

    type corner =
      | UpperLeft
      | UpperRight
      | LowerLeft
      | LowerRight;
    let corner = skiaCEnum(
      "sk_rrect_corner_t",
      [
        (UpperLeft, "UPPER_LEFT_SK_RRECT_CORNER"),
        (UpperRight, "UPPER_RIGHT_SK_RRECT_CORNER"),
        (LowerRight, "LOWER_RIGHT_SK_RRECT_CORNER"),
        (LowerLeft, "LOWER_LEFT_SK_RRECT_CORNER"),
      ],
    );
  };

  module Path = {
    type t;
    let t: typ(structure(t)) = structure("sk_path_t");
    let t = typedef(t, "sk_path_t");
  };
  
  module ColorSpace = {
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
  let colorType = skiaCEnum(
    "sk_colortype_t",
    [
      (Unknown, "UNKNOWN_SK_COLORTYPE"),
      (Alpha8, "ALPHA_8_SK_COLORTYPE"),
      (Rgb565, "RGB_565_SK_COLORTYPE"),
      (Argb4444, "ARGB_4444_SK_COLORTYPE"),
      (Rgba8888, "RGBA_8888_SK_COLORTYPE"),
      (Rgb888x, "RGB_888X_SK_COLORTYPE"),
      (Bgra8888, "BGRA_8888_SK_COLORTYPE"),
      (Rgba1010102, "RGBA_1010102_SK_COLORTYPE"),
      (Rgb101010x, "RGB_101010X_SK_COLORTYPE"),
      (Gray8, "GRAY_8_SK_COLORTYPE"),
      (RgbaF16, "RGBA_F16_SK_COLORTYPE"),
    ],
  );

  type alphaType =
    | Unknown
    | Opaque
    | Premul
    | Unpremul;
  let alphaType = skiaCEnum(
    "sk_alphatype_t",
    [
      (Unknown, "UNKNOWN_SK_ALPHATYPE"),
      (Opaque, "OPAQUE_SK_ALPHATYPE"),
      (Premul, "PREMUL_SK_ALPHATYPE"),
      (Unpremul, "UNPREMUL_SK_ALPHATYPE"),
    ],
  );

  module Data = {
    type t;
    let t: typ(structure(t)) = structure("sk_data_t");
    let t = typedef(t, "sk_data_t");
  };

  module ImageInfo = {
    type t;
    let t: typ(structure(t)) = structure("sk_imageinfo_t");
    let colorSpace = field(t, "colorspace", ptr_opt(ColorSpace.t));
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

  type pixelGeometry =
    | Unknown
    | RgbH
    | BgrH
    | RgbV
    | BgrV;
  let pixelGeometry = skiaCEnum(
    "sk_pixelgeometry_t",
    [
      (Unknown, "UNKNOWN_SK_PIXELGEOMETRY"),
      (RgbH, "RGB_H_SK_PIXELGEOMETRY"),
      (BgrH, "BGR_H_SK_PIXELGEOMETRY"),
      (RgbV, "RGB_V_SK_PIXELGEOMETRY"),
      (BgrV, "RGB_V_SK_PIXELGEOMETRY"),
    ],
  );

  module Gr = {
    type surfaceOrigin =
      | TopLeft
      | BottomLeft;
    let surfaceOrigin = skiaCEnum(
      "gr_surfaceorigin_t",
      [
        (TopLeft, "TOP_LEFT_GR_SURFACE_ORIGIN"),
        (BottomLeft, "BOTTOM_LEFT_GR_SURFACE_ORIGIN"),
      ],
    );
        
    module Gl = {
      module Interface = {
        type t;
        let t: typ(structure(t)) = structure("gr_glinterface_t");
        let t = typedef(t, "gr_glinterface_t");
      };

      module FramebufferInfo = {
        type t;
        let t: typ(structure(t)) = structure("gr_gl_framebufferinfo_t");
        let framebufferObjectId = field(t, "fFBOID", uint);
        let format = field(t, "fFormat", uint); // TODO this could also be an enum?
        seal(t);
        let t = typedef(t, "gr_gl_framebufferinfo_t");
      };
    };

    module Context = {
      type t;
      let t: typ(structure(t)) = structure("gr_context_t");
      let t = typedef(t, "gr_context_t");
    };

    module BackendRenderTarget = {
      type t;
      let t: typ(structure(t)) = structure("gr_backendrendertarget_t");
      let t = typedef(t, "gr_backendrendertarget_t");
    };

  };

  module TextBlob = {
    type t;
    let t: typ(structure(t)) = structure("sk_textblob_t");
    let t = typedef(t, "sk_textblob_t"); 

    module Builder = {
      type t;
      let t: typ(structure(t)) = structure("sk_textblob_builder_t");
      let t = typedef(t, "sk_textblob_builder_t"); 
    };
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
