cmake_minimum_required( VERSION 3.10 )

project( CALCULATOR C )

add_subdirectory( parser )
add_subdirectory( common )

include_directories( parser )
include_directories( common )

set( MAIN_SRC main.c )

add_executable( calculator ${MAIN_SRC} )

target_link_libraries( calculator PRIVATE parser )
