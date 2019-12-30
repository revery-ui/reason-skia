open Configurator.V1.Flags;
module C = Configurator.V1;

type os =
  | Windows
  | Mac
  | Linux
  | Unknown;

let uname = () => {
  let ic = Unix.open_process_in("uname");
  let uname = input_line(ic);
  let () = close_in(ic);
  uname;
};

let get_os =
  switch (Sys.os_type) {
  | "Win32" => Windows
  | _ =>
    switch (uname()) {
    | "Darwin" => Mac
    | "Linux" => Linux
    | _ => Unknown
    }
  };

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

    let ccopt = s => ["-ccopt", s];
    let cclib = s => ["-cclib", s];

    let flags =
      switch (get_os) {
      | Linux =>
        []
        @ ["-verbose"]
        @ cclib("-lfontconfig")
        @ cclib("-lfreetype")
        @ cclib("-lz")
        @ cclib("-lbz2")
        @ ccopt("-L" ++ Sys.getenv("FREETYPE2_LIB_PATH"))
        @ ccopt("-I" ++ Sys.getenv("FREETYPE2_INCLUDE_PATH"))
        @ ccopt("-I/usr/include")
      | _ => []
      };

    let libs =
      switch (get_os) {
      | Linux =>
        conf.libs
        @ [
          "-lfreetype",
          "-lfontconfig",
          "-lz",
          "-lbz2",
          "-L" ++ Sys.getenv("FREETYPE2_LIB_PATH"),
        ]
      | _ => conf.libs
      };

    write_sexp("flags.sexp", flags);
    write_lines("c_flags.txt", conf.cflags);
    write_sexp("c_flags.sexp", conf.cflags);
    write_sexp("c_library_flags.sexp", libs);
    write_lines("c_library_flags.txt", libs);
    write_sexp(
      "cclib_c_library_flags.sexp",
      libs |> List.map(o => ["-cclib", o]) |> List.flatten,
    );
  });
