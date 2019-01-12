#include "nonstd/byte.hpp"
#include <iostream>

using namespace nonstd;

int main()
{
    byte var = to_byte( 42 );

    std::cout <<
        "byte_CONFIG_NO_EXCEPTIONS: '" << byte_CONFIG_NO_EXCEPTIONS << "'\n" <<
        "byte_noexcept: '" byte_noexcept << "'\n";
}

// cl -nologo -I../include 02-no-exceptions.cpp && 02-no-exceptions
// g++ -Wall -fno-exceptions -I../include -o 02-no-exceptions 02-no-exceptions.cpp && 02-no-exceptions
