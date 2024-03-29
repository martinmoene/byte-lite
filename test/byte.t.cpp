//
// byte-lite, a C++17-like byte type for C++98 and later.
// For more information see https://github.com/martinmoene/gsl-lite
//
// Copyright 2017-2019 Martin Moene
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "byte-main.t.hpp"

// Use nonstd::byte instead of plain byte to prevent collisions with
// other byte declarations, such as in rpcndr.h (Windows kit).

// We have a chicken & egg problem here:
//   verifying operations via to_integer() that has yet to verified itself...

using namespace nonstd;

CASE( "byte: Allows to construct from integral via static cast (C++17)" )
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    nonstd::byte b = static_cast<nonstd::byte>( 4 );
    EXPECT( static_cast<unsigned char>(b) == 4 );
    EXPECT( to_integer<int>( b ) == 4 );
#else
    EXPECT( !!"enum class is not constructible from underlying type (no C++17)" );
#endif
}

CASE( "byte: Allows to construct from integral via byte() (C++17)" )
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    nonstd::byte b = nonstd::byte( 4 );
    EXPECT( to_integer<int>( b ) == 4 );
#else
    EXPECT( !!"enum class is not constructible from underlying type (no C++17)" );
#endif
}

CASE( "byte: Allows to construct from integral via to_byte()" )
{
    nonstd::byte b = to_byte( 4 );
    EXPECT( to_integer<int>( b ) == 4 );
}

CASE( "byte: Allows to convert to integral via to_integer()" )
{
    nonstd::byte b = to_byte( 4 );
    EXPECT( to_integer<int>( b ) == 4 );
}

CASE( "byte: Allows to convert to integral via to_integer(), using default type" )
{
#if byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
    nonstd::byte b = to_byte( 4 );
    EXPECT( to_integer( b ) == 4 );
#else
    EXPECT( !!"No default function template argument (no C++11)" );
#endif
}

CASE( "byte: Allows comparison operations" )
{
    nonstd::byte a = to_byte( 3 );
    nonstd::byte b = to_byte( 7 );

    EXPECT(     a == a );
    EXPECT(     a != b );

    EXPECT(     a <  b );
    EXPECT(     a <= a );
    EXPECT(     a <= b );

    EXPECT(     b >  a );
    EXPECT(     b >= a );
    EXPECT(     b >= b );

    EXPECT_NOT( a == b );
    EXPECT_NOT( a != a );
    EXPECT_NOT( b <  a );
    EXPECT_NOT( a >  b );
}

CASE( "byte: Allows bitwise or operation" )
{
    nonstd::byte const b = to_byte( 0xa5 );

    EXPECT( ( b | b ) == b );
    EXPECT( ( b | to_byte( 0x00 ) ) == b );
    EXPECT( ( b | to_byte( 0xff ) ) == to_byte( 0xff ) );
}

CASE( "byte: Allows bitwise and operation" )
{
    nonstd::byte const b = to_byte( 0xa5 );

    EXPECT( ( b & b ) == b );
    EXPECT( ( b & to_byte( 0xff ) ) == b );
    EXPECT( ( b & to_byte( 0x00 ) ) == to_byte( 0x00 ) );
}

CASE( "byte: Allows bitwise x-or operation" )
{
    nonstd::byte const b = to_byte( 0xa5 );

    EXPECT( ( b ^ b ) == to_byte( 0 ) );
    EXPECT( ( b ^ to_byte( 0x00 ) ) ==  b );
    EXPECT( ( b ^ to_byte( 0xff ) ) == ~b );
}

CASE( "byte: Allows bitwise or assignment" )
{
    SETUP("") {

    nonstd::byte const b_org = to_byte( 0xa5 );
    nonstd::byte       b     = b_org;

    SECTION("Identity") { EXPECT( ( b |= b               ) == b_org           ); }
    SECTION("Identity") { EXPECT( ( b |= to_byte( 0x00 ) ) == b_org           ); }
    SECTION("Saturate") { EXPECT( ( b |= to_byte( 0xff ) ) == to_byte( 0xff ) ); }
    }
}

CASE( "byte: Allows bitwise and assignment" )
{
    SETUP("") {

    nonstd::byte const b_org = to_byte( 0xa5 );
    nonstd::byte       b     = b_org;

    SECTION("Identity") { EXPECT( ( b &= b               ) == b_org           ); }
    SECTION("Identity") { EXPECT( ( b &= to_byte( 0xff ) ) == b_org           ); }
    SECTION("Clear"   ) { EXPECT( ( b &= to_byte( 0x00 ) ) == to_byte( 0x00 ) ); }
    }
}

CASE( "byte: Allows bitwise x-or assignment" )
{
    SETUP("") {

    nonstd::byte const b_org = to_byte( 0xa5 );
    nonstd::byte       b     = b_org;

    SECTION("Identity") { EXPECT( ( b ^= b               ) == to_byte( 0 ) ); }
    SECTION("Identity") { EXPECT( ( b ^= to_byte( 0x00 ) ) ==  b_org       ); }
    SECTION("Invert"  ) { EXPECT( ( b ^= to_byte( 0xff ) ) == ~b_org       ); }
    }
}

CASE( "byte: Allows shift-left operation" )
{
    nonstd::byte const b = to_byte( 0xa5 );

    EXPECT( ( b << 3 ) == to_byte( to_uchar( b ) << 3 ) );
}

CASE( "byte: Allows shift-right operation" )
{
    nonstd::byte const b = to_byte( 0xa5 );

    EXPECT( ( b >> 3 ) == to_byte( to_uchar( b ) >> 3 ) );
}

CASE( "byte: Allows shift-left assignment" )
{
    nonstd::byte const b_org = to_byte( 0xa5 );
    nonstd::byte       b     = b_org;

    EXPECT( ( b <<= 3 ) == to_byte( to_uchar( b_org ) << 3 ) );
}

CASE( "byte: Allows shift-right assignment" )
{
    nonstd::byte const b_org = to_byte( 0xa5 );
    nonstd::byte       b     = b_org;

    EXPECT( ( b >>= 3 ) == to_byte( to_uchar( b_org ) >> 3 ) );
}

CASE( "byte: Allows strict aliasing" )
{
    struct F {
        static int f( int & i, nonstd::byte & r )
        {
           r <<= 1;
           return i;
        }
    };

    // Allow for both little and big endianness:

   int i = 7;

   unsigned char & first =    reinterpret_cast<unsigned char&>(  i );
   unsigned char & last  = *( reinterpret_cast<unsigned char*>( &i ) + sizeof(int) - 1 );

   const bool big    = first == 0 && last == 7;
   const bool little = first == 7 && last == 0;

   unsigned char & lsb = little ? first : last;

   EXPECT( big != little );
   EXPECT(  14 == F::f( i, reinterpret_cast<nonstd::byte&>( lsb ) ) );
}

CASE( "byte: Provides constexpr non-assignment operations (C++11)" )
{
#if byte_HAVE_CONSTEXPR_11
    static_assert( to_byte( 0xa5 ) == to_byte( 0xa5 )                      , "" );
    static_assert(          0xa5   == to_integer<int>( to_byte( 0xa5 )    ), "" );

    static_assert( to_byte( 0x02 ) == ( to_byte( 0x01 ) << 1              ), "" );
    static_assert( to_byte( 0x01 ) == ( to_byte( 0x02 ) >> 1              ), "" );

    static_assert( to_byte( 0x01 ) == ( to_byte( 0x03 ) & to_byte( 0x01 ) ), "" );
    static_assert( to_byte( 0x01 ) == ( to_byte( 0x00 ) | to_byte( 0x01 ) ), "" );
    static_assert( to_byte( 0x00 ) == ( to_byte( 0x01 ) ^ to_byte( 0x01 ) ), "" );

    static_assert( to_byte( 0xff ) ==  ~to_byte( 0x00 ), "" );
#endif
}

CASE( "byte: Provides constexpr assignment operations (C++14)" )
{
#if byte_HAVE_CONSTEXPR_14
//  ...
#endif
}

// end of file
