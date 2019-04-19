open Configurator.V1

let () =
main ~name:"discover" (fun c ->
let default: Pkg_config.package_conf = { libs = []; cflags = [] } in
let config =
  match Pkg_config.get c with
  | None -> default
  | Some pkg_config ->
     match (Pkg_config.query pkg_config ~package:"skia") with
     | None -> default
     | Some deps -> deps
in

Flags.write_sexp "cxx_flags.sexp" config.cflags;
Flags.write_sexp "c_library_flags.sexp" config.libs)
