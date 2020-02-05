open Skia;
open TestFramework;

describe("Color", ({test, _}) => {
  test("makeArgb", ({expect}) => {
    let color = Color.makeArgb(0x1A, 0x1B, 0x1C, 0x1D);

    let a = Color.getA(color);
    let r = Color.getR(color);
    let g = Color.getG(color);
    let b = Color.getB(color);

    expect.int(a).toBe(0x1A);
    expect.int(r).toBe(0x1B);
    expect.int(g).toBe(0x1C);
    expect.int(b).toBe(0x1D);
  });
});
