# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/byte-lite
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )

# At default, enable building and performing of tests and building of examples:

option( BYTE_LITE_OPT_BUILD_TESTS    "Build and perform byte-lite tests" ON )
option( BYTE_LITE_OPT_BUILD_EXAMPLES "Build byte-lite examples" OFF )

project( span_lite )

set( package_name "span-lite" )

# Interface library:

add_library(                
    ${package_name} INTERFACE )
    
target_include_directories( 
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

enable_testing()

if ( BYTE_LITE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( BYTE_LITE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
