cmake_minimum_required( VERSION 3.10 )

project( COMMON C )

set( COMMON_SRC utils.c )

add_library( common SHARED ${COMMON_SRC} )
