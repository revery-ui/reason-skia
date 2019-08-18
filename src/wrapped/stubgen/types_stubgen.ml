let prefix = "skia_wrapped_stub"

let prologue = "

"

let () =
  print_endline prologue;
  Cstubs.Types.write_c Format.std_formatter (module SkiaWrappedBindingsTypes.M)
