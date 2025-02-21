cmake_minimum_required( VERSION 3.10 )

project( SCOPE C )

set( SCOPE_SRC list.c scope.c )
set( SCOPE_TARGET scope )

add_library( ${SCOPE_TARGET} SHARED ${SCOPE_SRC} )
