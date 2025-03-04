cmake_minimum_required( VERSION 3.10 )

project( COMPILER C )

add_subdirectory( parser )
add_subdirectory( scope )
add_subdirectory( tree )

include_directories( parser )
include_directories( scope )
include_directories( tree )

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
)

target_link_libraries( ${TEST_TARGET} PRIVATE 
    parser
    scope
    tree
)
