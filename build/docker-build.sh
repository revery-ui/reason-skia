source /opt/rh/llvm-toolset-7.0/enable
clang -v
clang++ -v

esy echo '#{esy-libjpeg-turbo.lib}'
esy ls '#{esy-libjpeg-turbo.lib}'

esy install
esy build

esy @example install
esy @example build
esy @example run
