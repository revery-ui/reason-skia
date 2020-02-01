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
    let framework = s => ["-framework", s];
    let flags =
      switch (get_os) {
      | Linux =>
        []
        @ ["-verbose"]
        @ cclib("-lfontconfig")
        @ cclib("-lfreetype")
        @ cclib("-lz")
        @ cclib("-lbz2")
        @ cclib("-lskia")
        @ ccopt("-L" ++ Sys.getenv("FREETYPE2_LIB_PATH"))
        @ ccopt("-L" ++ Sys.getenv("SKIA_LIB_PATH"))
        @ ccopt("-L" ++ Sys.getenv("JPEG_LIB_PATH"))
        @ ccopt("-I" ++ Sys.getenv("FREETYPE2_INCLUDE_PATH"))
        @ ccopt("-I" ++ Sys.getenv("SKIA_INCLUDE_PATH"))
        @ cclib("-ljpeg")
        @ ccopt("-I/usr/include")
        @ ccopt("-lstdc++")
      | _ => []
      };

    let cflags =
      switch (get_os) {
      | Mac =>
        []
        @ ["-I" ++ Sys.getenv("SKIA_INCLUDE_PATH")]
        @ ["-I" ++ Sys.getenv("SKIA_INCLUDE_PATH") ++ "/c"]
      | Linux =>
        //conf.cflags
        []
        @ ["-lskia"]
        @ ["-I" ++ Sys.getenv("SKIA_INCLUDE_PATH")]
        @ ["-I" ++ Sys.getenv("SKIA_INCLUDE_PATH") ++ "/c"]
        @ ["-L" ++ Sys.getenv("SKIA_LIB_PATH")]
        @ ["-L" ++ Sys.getenv("JPEG_LIB_PATH")]
        @ ["-lstdc++"]
        @ ["-ljpeg"]
      | _ => conf.cflags
      };

    let libs =
      switch (get_os) {
      | Mac =>
        []
        @ ["-L" ++ Sys.getenv("JPEG_LIB_PATH")]
        @ ["-L" ++ Sys.getenv("SKIA_LIB_PATH")]
        @ ["-L" ++ Sys.getenv("FREETYPE2_LIB_PATH")]
        @ framework("CoreServices")
        @ framework("CoreGraphics")
        @ framework("CoreText")
        @ framework("CoreFoundation")
        @ ["-lskia"]
        @ ["-lstdc++"]
        @ [Sys.getenv("JPEG_LIB_PATH") ++ "/libturbojpeg.a"]
      | Linux =>
        //conf.libs
        []
        @ [
          "-lskia",
          "-lfreetype",
          "-lfontconfig",
          "-lz",
          "-lbz2",
          "-L" ++ Sys.getenv("JPEG_LIB_PATH"),
          "-ljpeg",
          "-lpthread",
          "-lstdc++",
          "-L" ++ Sys.getenv("SKIA_LIB_PATH"),
          "-L" ++ Sys.getenv("FREETYPE2_LIB_PATH"),
        ]
      | _ => conf.libs
      };

    write_sexp("flags.sexp", flags);
    write_lines("c_flags.txt", cflags);
    write_sexp("c_flags.sexp", cflags);
    write_sexp("c_library_flags.sexp", libs);
    write_lines("c_library_flags.txt", libs);
    write_sexp(
      "cclib_c_library_flags.sexp",
      libs |> List.map(o => ["-cclib", o]) |> List.flatten,
    );
  });
