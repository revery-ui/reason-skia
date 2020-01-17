source /opt/rh/llvm-toolset-7.0/enable
clang -v
clang++ -v

pkg-config --list-all

esy install
esy build

esy @example install
esy @example build
esy @example run
