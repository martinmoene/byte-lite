// Copyright 2017-2018 Martin Moene
//
// https://github.com/martinmoene/byte-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_byte_LITE_H_INCLUDED
#define TEST_byte_LITE_H_INCLUDED

#include "nonstd/byte.hpp"

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include <iostream>

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

inline std::ostream & operator<<( std::ostream & os, byte const & v )
{
    return os << "[byte:" << std::hex << "0x" << to_integer<int>(  v ) << "]";
}

}

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#include "lest_cpp03.hpp"

extern lest::tests & specification();

#define CASE( name ) lest_CASE( specification(), name )

#endif // TEST_byte_LITE_H_INCLUDED

// end of file
