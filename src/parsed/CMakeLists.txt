cmake_minimum_required( VERSION 3.10 )

project( PARSED C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../scope )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../tree )

set( PARSED_SRC parsed.c )
set( PARSED_TARGET parsed )

add_library( ${PARSED_TARGET} SHARED ${PARSED_SRC} )

target_link_libraries( ${PARSED_TARGET} PUBLIC
    scope
    tree
)
