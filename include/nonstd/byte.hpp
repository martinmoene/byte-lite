//
// byte-lite, a C++17-like byte type for C++98 and later.
// For more information see https://github.com/martinmoene/byte-lite
//
// Copyright (c) 2017-2018 Martin Moene
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#ifndef NONSTD_BYTE_LITE_HPP
#define NONSTD_BYTE_LITE_HPP

#define  byte_lite_VERSION "0.1.0"

// byte-lite configuration:

// byte-lite alignment configuration:

// Compiler detection (C++17 is speculative):

#define byte_CPP11_OR_GREATER  ( __cplusplus >= 201103L )
#define byte_CPP14_OR_GREATER  ( __cplusplus >= 201402L )
#define byte_CPP17_OR_GREATER  ( __cplusplus >= 201700L )

#if defined( _MSC_VER ) && !defined( __clang__ )
# define byte_COMPILER_MSVC_VERSION ( _MSC_VER / 10 - 10 * ( 5 + ( _MSC_VER < 1900 ) ) )
#else
# define byte_COMPILER_MSVC_VERSION 0
#endif

#define byte_COMPILER_VERSION( major, minor, patch ) ( 10 * ( 10 * major + minor ) + patch )

#if defined __clang__
# define byte_COMPILER_CLANG_VERSION byte_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define byte_COMPILER_CLANG_VERSION 0
#endif

#if defined __GNUC__
# define byte_COMPILER_GNUC_VERSION byte_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define byte_COMPILER_GNUC_VERSION 0
#endif

// Compiler non-strict aliasing:

#if defined __clang__ || defined __GNUC__
# define byte_may_alias  __attribute__((__may_alias__))
#else
# define byte_may_alias
#endif

// Presence of C++11 language features:

#if byte_CPP11_OR_GREATER || byte_COMPILER_MSVC_VERSION >= 120
# define byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  1
# define byte_HAVE_UNDERLYING_TYPE  1
#endif

#if byte_CPP11_OR_GREATER || byte_COMPILER_MSVC_VERSION >= 140
# define byte_HAVE_CONSTEXPR_11  1
# define byte_HAVE_ENUM_CLASS  1
# define byte_HAVE_EXPLICIT_CONVERSION  1
# define byte_HAVE_NOEXCEPT  1
#endif

// Presence of C++14 language features:

#if byte_CPP14_OR_GREATER
# define byte_HAVE_CONSTEXPR_14  1
#endif

// Presence of C++17 language features:

#if byte_CPP17_OR_GREATER
# define byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE  1
#endif

// Presence of C++ library features:

#if byte_CPP11_OR_GREATER || byte_COMPILER_MSVC_VERSION >= 90
# define byte_HAVE_TYPE_TRAITS  1
#endif

// For the rest, consider VC14 as C++11 for byte-lite:

#if byte_COMPILER_MSVC_VERSION >= 140
# undef  byte_CPP11_OR_GREATER
# define byte_CPP11_OR_GREATER  1
#endif

// C++ feature usage:

#if byte_HAVE_CONSTEXPR_11
# define byte_constexpr constexpr
#else
# define byte_constexpr /*constexpr*/
#endif

#if byte_HAVE_CONSTEXPR_14
# define byte_constexpr14 constexpr
#else
# define byte_constexpr14 /*constexpr*/
#endif

#if byte_HAVE_NOEXCEPT
# define byte_noexcept noexcept
#else
# define byte_noexcept /*noexcept*/
#endif

// additional includes:

#if byte_HAVE_TYPE_TRAITS
# include <type_traits>
#endif

// conditionally enabling:

#if byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
# define byte_ENABLE_IF_INTEGRAL_T(T)  \
    , class = typename std::enable_if<std::is_integral<T>::value>::type
#else
# define byte_ENABLE_IF_INTEGRAL_T(T)
#endif

#if byte_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
# define byte_DEFAULT_TEMPLATE_ARG(T)  \
    = T
#else
# define byte_DEFAULT_TEMPLATE_ARG(T)
#endif

namespace nonstd {

namespace detail {
}

#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
  enum class byte_may_alias byte : unsigned char {};
#else
  struct byte_may_alias byte { typedef unsigned char type; type v; };
#endif

template< class IntegerType  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr byte to_byte( IntegerType v ) byte_noexcept
{
#if   byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    return static_cast<byte>( v );
#elif byte_HAVE_CONSTEXPR_11
    return { static_cast<typename byte::type>( v ) };
#else
    byte b = { static_cast<typename byte::type>( v ) }; return b;
#endif
}

#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE

template< class IntegerType = typename std::underlying_type<byte>::type  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr IntegerType to_integer( byte b ) byte_noexcept
{
    return static_cast<IntegerType>( b );
}

#else

template< class IntegerType  byte_DEFAULT_TEMPLATE_ARG(typename byte::type)  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr IntegerType to_integer( byte b ) byte_noexcept
{
    return b.v;
}
#endif

inline byte_constexpr unsigned char to_uchar( byte b ) byte_noexcept
{
    return to_integer<unsigned char>( b );
}

inline byte_constexpr unsigned char to_uchar( int i ) byte_noexcept
{
    return static_cast<unsigned char>( i );
}

#if ! byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE

inline byte_constexpr bool operator==( byte l, byte r ) byte_noexcept
{
    return l.v == r.v;
}

inline byte_constexpr bool operator!=( byte l, byte r ) byte_noexcept
{
    return !( l == r );
}

inline byte_constexpr bool operator< ( byte l, byte r ) byte_noexcept
{
    return l.v < r.v;
}

inline byte_constexpr bool operator<=( byte l, byte r ) byte_noexcept
{
    return !( r < l );
}

inline byte_constexpr bool operator> ( byte l, byte r ) byte_noexcept
{
    return ( r < l );
}

inline byte_constexpr bool operator>=( byte l, byte r ) byte_noexcept
{
    return !( l < r );
}
#endif

template< class IntegerType  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr14 byte & operator<<=( byte & b, IntegerType shift ) byte_noexcept
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    return b = to_byte( to_uchar( b ) << shift );
#else
    b.v = to_uchar( b.v << shift ); return b;
#endif
}

template< class IntegerType  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr14 byte & operator>>=( byte & b, IntegerType shift ) byte_noexcept
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    return b = to_byte( to_uchar( b ) >> shift );
#else
    b.v = to_uchar( b.v >> shift ); return b;
#endif
}

template< class IntegerType  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr byte operator<<( byte b, IntegerType shift ) byte_noexcept
{
    return to_byte( to_uchar( b ) << shift );
}

template< class IntegerType  byte_ENABLE_IF_INTEGRAL_T( IntegerType ) >
inline byte_constexpr byte operator>>( byte b, IntegerType shift ) byte_noexcept
{
    return to_byte( to_uchar( b ) >> shift );
}

inline byte_constexpr14 byte & operator|=( byte & l, byte r ) byte_noexcept
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    return l = to_byte( to_uchar( l ) | to_uchar( r ) );
#else
    l.v = to_uchar( l ) | to_uchar( r ); return l;
#endif
}

inline byte_constexpr14 byte & operator&=( byte & l, byte r ) byte_noexcept
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    return l = to_byte( to_uchar( l ) & to_uchar( r ) );
#else
    l.v = to_uchar( l ) & to_uchar( r ); return l;
#endif
}

inline byte_constexpr14 byte & operator^=( byte & l, byte r ) byte_noexcept
{
#if byte_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    return l = to_byte( to_uchar( l ) ^ to_uchar (r ) );
#else
    l.v = to_uchar( l ) ^ to_uchar (r ); return l;
#endif
}

inline byte_constexpr byte operator|( byte l, byte r ) byte_noexcept
{
    return to_byte( to_uchar( l ) | to_uchar( r ) );
}

inline byte_constexpr byte operator&( byte l, byte r ) byte_noexcept
{
    return to_byte( to_uchar( l ) & to_uchar( r ) );
}

inline byte_constexpr byte operator^( byte l, byte r ) byte_noexcept
{
    return to_byte( to_uchar( l ) ^ to_uchar( r ) );
}

inline byte_constexpr byte operator~( byte b ) byte_noexcept
{
    return to_byte( ~to_uchar( b ) );
}

} // namespace nonstd

#endif // NONSTD_BYTE_LITE_HPP

// end of file
