module Base = {
  let void = Ctypes.void;
};

module M = (F: Ctypes.TYPE) => {
  let void = Base.void;
};
