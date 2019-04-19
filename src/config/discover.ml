open Configurator.V1

let get_config c =
  let default = { cflags=[]; libs=[] } in
  match Pkg_config.get c with
  | None -> default
  | Some pkg_config -> (
      match Pkg_config.query pkg_config ~package:"skia" with
      | None -> default
      | Some config -> config
in

let () =
  main ~name:"discover" (fun c ->
      let config = get_config c in
      Flags.write_sexp "cxx_flags.sexp" config.cflags;
      Flags.write_sexp "c_library_flags.sexp" config.libs )
