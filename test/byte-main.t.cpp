// Copyright 2017-2018 Martin Moene
//
// https://github.com/martinmoene/byte-lite
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "byte-main.t.hpp"

#define byte_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define byte_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "byte-lite version" "[.byte][.version]" )
{
    byte_PRESENT( byte_lite_MAJOR );
    byte_PRESENT( byte_lite_MINOR );
    byte_PRESENT( byte_lite_PATCH );
    byte_PRESENT( byte_lite_VERSION );
}

CASE( "byte configuration" "[.byte][.config]" )
{
    byte_PRESENT( byte_HAVE_STD_BYTE );
    byte_PRESENT( byte_USES_STD_BYTE );
    byte_PRESENT( byte_CONFIG_SELECT_BYTE );
    byte_PRESENT( byte_BYTE_DEFAULT );
    byte_PRESENT( byte_BYTE_NONSTD );
    byte_PRESENT( byte_BYTE_STD );
    byte_PRESENT( byte_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    byte_PRESENT( __cplusplus );
}

CASE( "compiler version" "[.compiler]" )
{
#if byte_USES_STD_BYTE
    std::cout << "(Compiler version not available: using std::byte)\n";
#else
    byte_PRESENT( byte_COMPILER_CLANG_VERSION );
    byte_PRESENT( byte_COMPILER_GNUC_VERSION );
    byte_PRESENT( byte_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if byte_USES_STD_BYTE
    std::cout << "(Presence of C++ language features not available: using std::byte)\n";
#else
    byte_PRESENT( byte_HAVE_CONSTEXPR_11 );
    byte_PRESENT( byte_HAVE_CONSTEXPR_14 );
    byte_PRESENT( byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
    byte_PRESENT( byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
    byte_PRESENT( byte_HAVE_NOEXCEPT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if byte_USES_STD_BYTE
    std::cout << "(Presence of C++ library features not available: using std::byte)\n";
#else
    byte_PRESENT( byte_HAVE_TYPE_TRAITS );
#endif

#if defined _HAS_CPP0X
    byte_PRESENT( _HAS_CPP0X );
#else
    byte_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o byte-main.t.exe byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass

cl -EHsc -I../include/nonstd byte-main.t.cpp byte.t.cpp && byte-main.t.exe --pass
#endif

// end of file
