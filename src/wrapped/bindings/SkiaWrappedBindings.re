open Ctypes;

module SkiaTypes = SkiaWrappedTypes.M(Skia_generated_type_stubs);

module M = (F: FOREIGN) => {
  open F;

  type colorType = SkiaTypes.colorType;
  let colorType = SkiaTypes.colorType;
  type alphaType = SkiaTypes.alphaType;
  let alphaType = SkiaTypes.alphaType;

  module Color = {
    type t = Unsigned.uint32;
    let t = uint32_t;

    let makeArgb = foreign(
      "reason_skia_stub_sk_color_set_argb",
      int @-> int @-> int @-> int @-> returning(uint32_t),
    );
  };

  module Paint = {
    type t = ptr(SkiaTypes.Paint.t);
    let t = ptr(SkiaTypes.Paint.t);
    type style = SkiaTypes.Paint.style;
    let style = SkiaTypes.Paint.style;

    let allocate = foreign("sk_paint_new", void @-> returning(t));
    let delete = foreign("sk_paint_delete", t @-> returning(void));

    let setColor =
      foreign("sk_paint_set_color", t @-> Color.t @-> returning(void));
    let setAntiAlias = 
      foreign("sk_paint_set_antialias", t @-> bool @-> returning(void));
    let setStyle = 
      foreign("sk_paint_set_style", t @-> style @-> returning(void));
    let setStrokeWidth = 
      foreign("sk_paint_set_stroke_width", t @-> float @-> returning(void));
  };

  module Rect = {
    type t = ptr(SkiaTypes.Rect.t);
    let t = ptr(SkiaTypes.Rect.t);

    let makeEmpty = () => {
      let rect = allocate_n(SkiaTypes.Rect.t, 1);
      setf(!@rect, SkiaTypes.Rect.left, 0.);
      setf(!@rect, SkiaTypes.Rect.top, 0.);
      setf(!@rect, SkiaTypes.Rect.right, 0.);
      setf(!@rect, SkiaTypes.Rect.bottom, 0.);
      rect;
    };
    let makeLtrb = (left, top, right, bottom) => {
      let rect = allocate_n(SkiaTypes.Rect.t, 1);
      setf(!@rect, SkiaTypes.Rect.left, left);
      setf(!@rect, SkiaTypes.Rect.top, top);
      setf(!@rect, SkiaTypes.Rect.right, right);
      setf(!@rect, SkiaTypes.Rect.bottom, bottom);
      rect;
    };
  };

  module Path = {
    type t = ptr(SkiaTypes.Path.t);
    let t = ptr(SkiaTypes.Path.t);

    let allocate = foreign("sk_path_new", void @-> returning(t));
    let delete = foreign("sk_path_delete", t @-> returning(void));

    let moveTo =
      foreign("sk_path_move_to", t @-> float @-> float @-> returning(void));
    let lineTo =
      foreign("sk_path_line_to", t @-> float @-> float @-> returning(void));
    let cubicTo =
      foreign(
        "sk_path_cubic_to",
        t @->
        float @->
        float @->
        float @->
        float @->
        float @->
        float @->
        returning(void),
      );
  };

  module Colorspace = {
    type t = ptr(SkiaTypes.Colorspace.t);
    let t = ptr(SkiaTypes.Colorspace.t);
  };
  
  module Data = {
    type t = ptr(SkiaTypes.Data.t);
    let t = ptr(SkiaTypes.Data.t);

    let delete = foreign("sk_data_unref", t @-> returning(void));

    let getData = foreign("sk_data_get_data", t @-> returning(ptr(void)));
    let getSize = foreign("sk_data_get_size", t @-> returning(size_t));
  };

  module Imageinfo = {
    type t = ptr(SkiaTypes.Imageinfo.t);
    let t = ptr(SkiaTypes.Imageinfo.t);
    
    let make = (width, height, colorType, alphaType, colorspace) => {
      let imageinfo = allocate_n(SkiaTypes.Imageinfo.t, 1);
      setf(!@imageinfo, SkiaTypes.Imageinfo.width, width);
      setf(!@imageinfo, SkiaTypes.Imageinfo.height, height);
      setf(!@imageinfo, SkiaTypes.Imageinfo.colorType, colorType);
      setf(!@imageinfo, SkiaTypes.Imageinfo.alphaType, alphaType);
      setf(!@imageinfo, SkiaTypes.Imageinfo.colorspace, colorspace);
      imageinfo;
    };
  };

  module Image = {
    type t = ptr(SkiaTypes.Image.t);
    let t = ptr(SkiaTypes.Image.t);

    let delete = foreign("sk_image_unref", t @-> returning(void));

    let encode = foreign("sk_image_encode", t @-> returning(Data.t));
  };

  type pixelGeometry = SkiaTypes.pixelGeometry;
  let pixelGeometry = SkiaTypes.pixelGeometry;

  module Gr = {
    type surfaceOrigin = SkiaTypes.Gr.surfaceOrigin;
    let surfaceOrigin = SkiaTypes.Gr.surfaceOrigin;

    module Gl = {
      module Interface = {
        type t = ptr(SkiaTypes.Gr.Gl.Interface.t);
        let t = ptr(SkiaTypes.Gr.Gl.Interface.t);
      };

      module FramebufferInfo = {
        type t = ptr(SkiaTypes.Gr.Gl.FramebufferInfo.t);
        let t = ptr(SkiaTypes.Gr.Gl.FramebufferInfo.t);

        let make = (framebufferObjectId, format) => {
          let framebufferInfo = allocate_n(SkiaTypes.Gr.Gl.FramebufferInfo.t, 1);
          setf(!@framebufferInfo, SkiaTypes.Gr.Gl.FramebufferInfo.framebufferObjectId, framebufferObjectId);
          setf(!@framebufferInfo, SkiaTypes.Gr.Gl.FramebufferInfo.format, format);
          framebufferInfo;
        };
      };
    };

    module Context = {
      type t = ptr(SkiaTypes.Gr.Context.t);
      let t = ptr(SkiaTypes.Gr.Context.t);

      let makeGl = foreign("gr_context_make_gl", ptr_opt(SkiaTypes.Gr.Gl.Interface.t) @-> returning(t));
    };

    module BackendRenderTarget = {
      type t = ptr(SkiaTypes.Gr.BackendRenderTarget.t);
      let t = ptr(SkiaTypes.Gr.BackendRenderTarget.t);

      let makeGl = foreign("gr_backendrendertarget_new_gl", int @-> int @-> int @-> int @-> ptr(SkiaTypes.Gr.Gl.FramebufferInfo.t) @-> returning(t));
    };
  };

  module Canvas = {
    type t = ptr(SkiaTypes.Canvas.t);
    let t = ptr(SkiaTypes.Canvas.t);

    let drawPaint =
      foreign("sk_canvas_draw_paint", t @-> Paint.t @-> returning(void));
    let drawRect =
      foreign(
        "sk_canvas_draw_rect",
        t @-> Rect.t @-> Paint.t @-> returning(void),
      );
    let drawOval =
      foreign(
        "sk_canvas_draw_oval",
        t @-> Rect.t @-> Paint.t @-> returning(void),
      );
    let drawPath =
      foreign(
        "sk_canvas_draw_path",
        t @-> Path.t @-> Paint.t @-> returning(void),
      );
  };

  module SurfaceProps = {
    type t = ptr(SkiaTypes.SurfaceProps.t);
    let t = ptr(SkiaTypes.SurfaceProps.t);

    let make = foreign("sk_surfaceprops_new", uint32_t @-> pixelGeometry @-> returning(t));
  };

  module Surface = {
    type t = ptr(SkiaTypes.Surface.t);
    let t = ptr(SkiaTypes.Surface.t);
      
    let allocateRaster =
      foreign(
        "sk_surface_new_raster",
        Imageinfo.t @-> size_t @-> ptr_opt(SkiaTypes.SurfaceProps.t) @-> returning(t),
      );
    let allocateWithRenderTarget =
      foreign(
        "sk_surface_new_render_target", 
        // TODO clarify which parameters are optional here
        Gr.Context.t @->
        bool @->
        Imageinfo.t @->
        int @->
        Gr.surfaceOrigin @->
        SurfaceProps.t @->
        bool @->
        returning(t),
      );
    let allocateWithBackendRenderTarget =
      foreign(
        "sk_surface_new_backend_render_target", 
        // TODO clarify which parameters are optional here
        Gr.Context.t @->
        Gr.BackendRenderTarget.t @->
        Gr.surfaceOrigin @->
        colorType @->
        ptr_opt(SkiaTypes.Colorspace.t) @->
        ptr_opt(SkiaTypes.SurfaceProps.t) @->
        returning(t),
      );
    let delete = foreign("sk_surface_unref", t @-> returning(void));

    let getCanvas =
      foreign("sk_surface_get_canvas", t @-> returning(Canvas.t));
    let allocateImageSnapshot =
      foreign(
        "sk_surface_new_image_snapshot",
        t @-> returning(Image.t),
      );
  };
};
