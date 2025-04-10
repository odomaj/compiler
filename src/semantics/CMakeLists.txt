cmake_minimum_required( VERSION 3.10 )

project( SEMANTICS C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../scope )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../tree )

set( SEMANTICS_SRC semantics.c )
set( SEMANTICS_TARGET semantics )

add_library( ${SEMANTICS_TARGET} SHARED ${SEMANTICS_SRC} )

target_link_libraries( ${SEMANTICS_TARGET} PUBLIC
    scope
    tree
)
