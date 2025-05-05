cmake_minimum_required( VERSION 3.10 )

project( PARSER C )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../scope )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../tree )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../common )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

find_package( FLEX REQUIRED )
find_package( BISON REQUIRED )

set( FLEX_SRC scanner.l )
set( BISON_SRC parser.y )

set( FLEX_TARGET ${CMAKE_CURRENT_BINARY_DIR}/scanner_.c )
set( BISON_TARGET ${CMAKE_CURRENT_BINARY_DIR}/parser_.c )
set( PARSER_TARGET parser )

flex_target(lexer ${FLEX_SRC} ${FLEX_TARGET})
bison_target(parser ${BISON_SRC} ${BISON_TARGET})

add_flex_bison_dependency(lexer parser)

add_library( ${PARSER_TARGET} STATIC
    ${FLEX_TARGET}
    ${BISON_TARGET}
)

target_link_libraries( ${PARSER_TARGET} PUBLIC
    scope
    tree
    common
)
