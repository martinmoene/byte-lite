@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
clang -std=%std% -O2 -Wall -Wextra -Wno-unused-parameter -o byte-lite.t.exe -I../include/nonstd byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe
@endlocal

