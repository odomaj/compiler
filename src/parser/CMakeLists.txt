cmake_minimum_required( VERSION 3.10 )

project( PARSER C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../common )

set( PARSER_SRC parser.c )

add_library( parser STATIC ${PARSER_SRC} )

target_link_libraries( parser PUBLIC common )
