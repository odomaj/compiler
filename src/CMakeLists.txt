cmake_minimum_required( VERSION 3.10 )

project( COMPILER C )

set (CMAKE_C_STANDARD 11)

add_subdirectory( parser )
add_subdirectory( scope )
add_subdirectory( tree )
add_subdirectory( code_gen )
add_subdirectory( common )

include_directories( parser )
include_directories( scope )
include_directories( tree )
include_directories( code_gen )
include_directories( common )

set( MAIN_SRC main.c )
set( MAIN_TARGET compiler )

set( TEST_SRC test.c )
set( TEST_TARGET compiler_test )

add_executable( ${MAIN_TARGET} ${MAIN_SRC} )
add_executable( ${TEST_TARGET} ${TEST_SRC} )

target_link_libraries( ${MAIN_TARGET} PRIVATE 
    parser
    scope
    tree
    code_gen
)

target_link_libraries( ${TEST_TARGET} PRIVATE 
    parser
    scope
    tree
    code_gen
)
