@echo off & setlocal
set std=%1
if not "%std%"=="" set std=-std:%std%

cl -W3 -EHsc %std% -I../include/nonstd byte-main.t.cpp byte.t.cpp && byte-main.t.exe
endlocal
