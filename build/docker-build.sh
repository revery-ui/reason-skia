source /opt/rh/llvm-toolset-7.0/enable
clang -v
clang++ -v

esy install


esy echo '#{esy-libjpeg-turbo.lib}'
esy ls '#{esy-libjpeg-turbo.lib}'

echo "-- ESY BUILD"
esy build

esy ls '#{esy-libjpeg-turbo.lib}'

echo "-- TRY LS HARDCODED PATH"

ls /root/.esy/3__________________________________________________________________________/i/esy_libjpeg_turbo-a63bd461/lib

echo "-- EXAMPLE INSTALL / BUILD"
esy @example install
esy @example build
esy @example run
