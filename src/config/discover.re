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

    let write_sexp = (fn, eles) => write_sexp(fn, eles);
    let write_txt = (fn, eles) => write_lines(fn, eles);

    write_txt("c_flags.txt", conf.cflags);
    write_sexp("c_library_flags.sexp", conf.libs);
    write_txt("c_library_flags.txt", conf.libs);
  });
