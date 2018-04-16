// Copyright (c) 2017 Martin Moene
//
// https://github.com/martinmoene/byte-lite
//
// This code is licensed under the MIT License (MIT).

#pragma once

#ifndef TEST_byte_LITE_H_INCLUDED
#define TEST_byte_LITE_H_INCLUDED

#include "byte.hpp"
#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

inline std::ostream & operator<<( std::ostream & os, ::nonstd::byte const & v )
{
    return os << "[byte:" << std::hex << "0x" << to_integer<int>(  v ) << "]";
}

}

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#endif // TEST_byte_LITE_H_INCLUDED

// end of file
