open Skia;
open TestFramework;

describe("Color", ({test, _}) => {
  test("makeArgb", ({expect}) => {
    let color = Color.makeArgb(0x1Al, 0x1Bl, 0x1Cl, 0x1Dl);

    let a = Color.getA(color) |> Int32.to_int;
    let r = Color.getR(color) |> Int32.to_int;
    let g = Color.getG(color) |> Int32.to_int;
    let b = Color.getB(color) |> Int32.to_int;

    expect.int(a).toBe(0x1A);
    expect.int(r).toBe(0x1B);
    expect.int(g).toBe(0x1C);
    expect.int(b).toBe(0x1D);
  })
});
