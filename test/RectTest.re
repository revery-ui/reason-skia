open Skia;
open TestFramework;

describe("Rect", ({test, _}) => {
  test("makeLtrb", ({expect}) => {
    let rect = Rect.makeLtrb(1., 2., 3., 4.);
    let left = Rect.getLeft(rect);
    let right = Rect.getRight(rect);
    let top = Rect.getTop(rect);
    let bottom = Rect.getBottom(rect);

    expect.float(left).toBeCloseTo(1.);
    expect.float(top).toBeCloseTo(2.);
    expect.float(right).toBeCloseTo(3.);
    expect.float(bottom).toBeCloseTo(4.);
  })
});
