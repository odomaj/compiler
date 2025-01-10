cmake_minimum_required( VERSION 3.10 )

project( SCANNER C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../common )

set( SCANNER_SRC scanner.c )

add_library( scanner STATIC ${SCANNER_SRC} )

target_link_libraries( scanner PUBLIC common )
