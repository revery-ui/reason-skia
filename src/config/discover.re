open Configurator.V1.Flags;
module C = Configurator.V1;

let () =
  C.main(~name="skia_wrapped", c => {
    let default: C.Pkg_config.package_conf = (
      {libs: [], cflags: []}: C.Pkg_config.package_conf
    );

    let conf =
      switch (C.Pkg_config.get(c)) {
      | None => default
      | Some(pc) =>
        switch (C.Pkg_config.query(pc, ~package="skia")) {
        | None => default
        | Some(deps) => deps
        }
      };

    write_lines("c_flags.txt", conf.cflags);
    write_sexp("c_flags.sexp", conf.cflags);
    write_sexp("c_library_flags.sexp", conf.libs);
    write_lines("c_library_flags.txt", conf.libs);
    write_sexp(
      "cclib_c_library_flags.sexp",
      conf.libs |> List.map(o => ["-cclib", o]) |> List.flatten,
    );
  });
