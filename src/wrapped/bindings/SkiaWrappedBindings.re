module M = (F: Ctypes.FOREIGN) => {
  let foreign = F.foreign;

  module C = {
    include Ctypes;
    let (@->) = F.(@->);
    let returning = F.returning;
  };

  let imported_draw_main =
    foreign(
      "draw_main",
      C.(SkiaWrappedBindingsTypes.Base.void @-> returning(int)),
    );

  let imported_my_c_function =
    foreign(
      "my_c_function",
      C.(SkiaWrappedBindingsTypes.Base.void @-> returning(int)),
    );
  let imported_my_bar_function =
    foreign(
      "my_bar_function",
      C.(SkiaWrappedBindingsTypes.Base.void @-> returning(int)),
    );
};
