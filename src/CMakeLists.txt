cmake_minimum_required( VERSION 3.10 )

project( CALCULATOR C )

add_subdirectory( parser )
add_subdirectory( scope )
add_subdirectory( tree )

include_directories( parser )
include_directories( scope )
include_directories( tree )

set( MAIN_SRC main.c )
set( TARGET compiler )

add_executable( ${TARGET} ${MAIN_SRC} )

target_link_libraries( ${TARGET} PRIVATE 
    parser
    scope
    tree
)
