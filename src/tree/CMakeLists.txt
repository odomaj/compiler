cmake_minimum_required( VERSION 3.10 )

project( TREE C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../scope )

set( TREE_SRC tree.c )
set( TREE_TARGET tree )

add_library( ${TREE_TARGET} SHARED ${TREE_SRC} )

target_link_libraries( ${TREE_TARGET} PUBLIC
    scope
)
