# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/byte-lite
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# byte-lite project and version, updated by script/update-version.py:

project( byte_lite LANGUAGES CXX )

set( byte_lite_version "0.1.0" )

# Toplevel or subproject:

if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    set( byte_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( byte_IS_TOPLEVEL_PROJECT FALSE )
endif()

# At default, enable building and performing of tests and building of examples:

option( BYTE_LITE_OPT_BUILD_TESTS    "Build and perform byte-lite tests" ${byte_IS_TOPLEVEL_PROJECT} )
option( BYTE_LITE_OPT_BUILD_EXAMPLES "Build byte-lite examples" OFF )

option( BYTE_LITE_OPT_SELECT_STD      "Select std::byte"    OFF )
option( BYTE_LITE_OPT_SELECT_NONSTD   "Select nonstd::byte" OFF )

include( GNUInstallDirs )

set( package_name "byte-lite" )
set( include_source_dir "${PROJECT_SOURCE_DIR}/include" )

# Interface library:

add_library(
    ${package_name} INTERFACE )

target_include_directories(
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

# Installation:

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# If requested, build and perform tests, build examples:

enable_testing()

if ( BYTE_LITE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( BYTE_LITE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
