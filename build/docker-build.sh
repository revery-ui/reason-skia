source /opt/rh/llvm-toolset-7.0/enable
clang -v
clang++ -v

esy install

echo "-- ESY BUILD"
esy build

echo "-- EXAMPLE INSTALL / BUILD"
esy @example install
esy @example build
esy @example run
