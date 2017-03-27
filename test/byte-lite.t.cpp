// Copyright (c) 2017 Martin Moene
//
// https://github.com/martinmoene/byte-lite
//
// This code is licensed under the MIT License (MIT).

#include "byte-lite.t.h"

#define byte_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define byte_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "__cplusplus" "[.stdc++]" )
{
    byte_PRESENT( __cplusplus );
}

CASE( "byte-lite version" "[.version]" )
{
    byte_PRESENT( byte_lite_VERSION );
}

CASE( "compiler version" "[.compiler]" )
{
#if byte_COMPILER_GNUC_VERSION
    byte_PRESENT( byte_COMPILER_GNUC_VERSION );
#else
    byte_ABSENT(  byte_COMPILER_GNUC_VERSION );
#endif

#if byte_COMPILER_MSVC_VERSION
    byte_PRESENT( byte_COMPILER_MSVC_VERSION );
#else
    byte_ABSENT(  byte_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
    byte_PRESENT( byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#else
    byte_ABSENT(  byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#endif

#if byte_HAVE_CONSTEXPR_11
    byte_PRESENT( byte_HAVE_CONSTEXPR_11 );
#else
    byte_ABSENT(  byte_HAVE_CONSTEXPR_11 );
#endif

#if byte_HAVE_CONSTEXPR_14
    byte_PRESENT( byte_HAVE_CONSTEXPR_14 );
#else
    byte_ABSENT(  byte_HAVE_CONSTEXPR_14 );
#endif

#if byte_HAVE_ENUM_CLASS
    byte_PRESENT( byte_HAVE_ENUM_CLASS );
#else
    byte_ABSENT(  byte_HAVE_ENUM_CLASS );
#endif

#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    byte_PRESENT( byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#else
    byte_ABSENT(  byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#endif

#if byte_HAVE_EXPLICIT_CONVERSION
    byte_PRESENT( byte_HAVE_EXPLICIT_CONVERSION );
#else
    byte_ABSENT(  byte_HAVE_EXPLICIT_CONVERSION );
#endif

#if byte_HAVE_NOEXCEPT
    byte_PRESENT( byte_HAVE_NOEXCEPT );
#else
    byte_ABSENT(  byte_HAVE_NOEXCEPT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if byte_HAVE_TYPE_TRAITS
    byte_PRESENT( byte_HAVE_TYPE_TRAITS );
#else
    byte_ABSENT(  byte_HAVE_TYPE_TRAITS );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o byte-lite.t.exe byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass

cl -EHsc -I../include/nonstd byte-lite.t.cpp byte.t.cpp && byte-lite.t.exe --pass
#endif

// end of file
