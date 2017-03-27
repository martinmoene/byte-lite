#include "byte.hpp"

#include <cassert>

using namespace nonstd;

int main()
{
    byte b1 = to_byte( 0x5a );  // to_byte() is non-standard, needed for pre-C++17
    byte b2 = to_byte( 0xa5 );

    byte r1 = b1 ^ b2; assert( 0xff == to_integer( r1 ) );  // not (yet) standard, needs C++11
    byte r2 = b1 ^ b2; assert( 0xff == to_integer<unsigned int>( r2 ) );
}

// cl -nologo -EHsc -I../include/nonstd 01-basic.cpp && 01-basic
// g++ -std=c++11 -Wall -I../include/nonstd -o 01-basic 01-basic.cpp && 01-basic
