# Copyright 2017 by Martin Moene
#
# https://github.com/martinmoene/byte-lite
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 2.8.12 )

project( test )

include_directories( "${PROJECT_SOURCE_DIR}/../include/nonstd" )

set( SOURCES byte-lite.t.cpp byte.t.cpp )

add_executable( byte-lite.t ${SOURCES} )

set( HAS_STD_FLAGS  FALSE )
set( HAS_CPP11_FLAG FALSE )
set( HAS_CPP14_FLAG FALSE )
set( HAS_CPP17_FLAG FALSE )

if( ${CMAKE_CXX_COMPILER_ID} MATCHES MSVC )
    add_compile_options( -W3 -EHsc -D_SCL_SECURE_NO_WARNINGS )

elseif( ${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR
        ${CMAKE_CXX_COMPILER_ID} MATCHES Clang )

    set( HAS_STD_FLAGS TRUE )

    # GNU: available -std flags depends on version
    if( ${CMAKE_CXX_COMPILER_ID} MATCHES GNU )
        execute_process(
            COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

        if( GCC_VERSION )
            if( NOT GCC_VERSION VERSION_LESS 4.8.0 )
                set( HAS_CPP11_FLAG TRUE )
            endif()
            if( NOT GCC_VERSION VERSION_LESS 4.9.2 )
                set( HAS_CPP14_FLAG TRUE )
            endif()
            if( NOT GCC_VERSION VERSION_LESS 5.0.0 )
                set( HAS_CPP17_FLAG TRUE )
            endif()
        endif()
    endif()

    # Clang: available -std flags depends on version
    if( ${CMAKE_CXX_COMPILER_ID} MATCHES Clang )
        execute_process(
            COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE CLANG_VERSION)

        if( CLANG_VERSION )
            if( NOT CLANG_VERSION VERSION_LESS 3.3.0 )
                set( HAS_CPP11_FLAG TRUE )
            endif()
# clang 3.5.0 -std=c++14: no member named 'gets' in the global namespace: using ::gets;
#            if( NOT CLANG_VERSION VERSION_LESS 3.4.0 )
#                set( HAS_CPP14_FLAG TRUE )
#            endif()
#            if( NOT CLANG_VERSION VERSION_LESS 3.5.0 )
#                set( HAS_CPP17_FLAG TRUE )
#            endif()
        endif()
    endif()

    add_executable( byte-lite-cpp98.t ${SOURCES} )
    target_compile_options( byte-lite-cpp98.t  PUBLIC -std=c++98 )

    add_executable( byte-lite-cpp03.t ${SOURCES} )
    target_compile_options( byte-lite-cpp03.t  PUBLIC -std=c++03 )

    if( HAS_CPP11_FLAG )
        add_executable( byte-lite-cpp11.t ${SOURCES} )
        target_compile_options( byte-lite-cpp11.t  PUBLIC -std=c++11 )
    endif()

    if( HAS_CPP14_FLAG )
        add_executable( byte-lite-cpp14.t ${SOURCES} )
        target_compile_options( byte-lite-cpp14.t  PUBLIC -std=c++14 )
    endif()

    if( HAS_CPP17_FLAG )
        add_executable( byte-lite-cpp17.t ${SOURCES} )
        target_compile_options( byte-lite-cpp17.t  PUBLIC -std=c++17 )
    endif()

    add_compile_options( -Wall -Wextra -Wno-unused-parameter )

elseif( ${CMAKE_CXX_COMPILER_ID} MATCHES Intel )
# as is
else()
# as is
endif()

# configure unit tests via CTest:

enable_testing()

if( NOT HAS_STD_FLAGS )
    add_test(     NAME test          COMMAND byte-lite.t --pass )
else()
    add_test(     NAME test-cpp98    COMMAND byte-lite-cpp98.t )
    add_test(     NAME test-cpp03    COMMAND byte-lite-cpp03.t )
    if( HAS_CPP11_FLAG )
        add_test( NAME test-cpp11    COMMAND byte-lite-cpp11.t )
    endif()
    if( HAS_CPP14_FLAG )
        add_test( NAME test-cpp14    COMMAND byte-lite-cpp14.t )
    endif()
    if( HAS_CPP17_FLAG )
        add_test( NAME test-cpp17    COMMAND byte-lite-cpp17.t )
    endif()
endif()
add_test(         NAME list_version  COMMAND byte-lite.t --version )
add_test(         NAME list_tags     COMMAND byte-lite.t --list-tags )
add_test(         NAME list_tests    COMMAND byte-lite.t --list-tests )

# end of file
