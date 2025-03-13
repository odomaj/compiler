cmake_minimum_required( VERSION 3.10 )

project( CODE_GEN C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../scope )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../tree )

set( CODE_GEN_SRC code_gen.c )
set( CODE_GEN_TARGET code_gen )

add_library( ${CODE_GEN_TARGET} SHARED ${CODE_GEN_SRC} )

target_link_libraries( ${CODE_GEN_TARGET} PUBLIC
    scope
    tree
)