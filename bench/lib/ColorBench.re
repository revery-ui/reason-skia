open BenchFramework;

open Skia;

let options = Reperf.Options.create(~iterations=100000, ());

module Data = {
  let initialColor = Skia.Color.makeArgb(0xFF, 0xFF, 0xFF, 0xFF);
};

let makeArgb = () => {
  let _: Skia.Color.t =
    Skia.Color.makeArgb(0xFF, 0xFF, 0xFF, 0xFF)
};

let getA = () => {
  let _: int =
    Skia.Color.getA(Data.initialColor);
};

bench(~name="Color: makeArgb", ~options, ~setup=() => (), ~f=makeArgb, ());
bench(~name="Color: getA", ~options, ~setup=() => (), ~f=makeArgb, ());

