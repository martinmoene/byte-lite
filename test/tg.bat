@setlocal
@set std=%1
@if "%std%"=="" set std=c++11

g++ -std=%std% -O2 -Wall -Wextra -fstrict-aliasing -Wstrict-aliasing=2 -Wno-unused-parameter -o byte-main.t.exe -I../include/nonstd byte-main.t.cpp byte.t.cpp && byte-main.t.exe
@endlocal

