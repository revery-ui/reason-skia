open BenchFramework;

open Skia;

let options = Reperf.Options.create(~iterations=100000, ());

module Data = {
  let initialColor = Skia.Color.makeArgb(0xFFl, 0xFFl, 0xFFl, 0xFFl);
};

let makeArgb = () => {
  let _: Skia.Color.t = Skia.Color.makeArgb(0xFFl, 0xFFl, 0xFFl, 0xFFl);
  ();
};

let getA = () => {
  let _: int32 = Skia.Color.getA(Data.initialColor);
  ();
};

bench(~name="Color: makeArgb", ~options, ~setup=() => (), ~f=makeArgb, ());
bench(~name="Color: getA", ~options, ~setup=() => (), ~f=makeArgb, ());
