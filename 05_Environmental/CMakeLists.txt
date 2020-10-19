cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME pcre_gui)
set(EXE_NAME pcre_demo)
project (${PROJECT_NAME})

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -Wall)
INCLUDE(CheckIncludeFiles)


find_library(LIB_NCURSES ncursesw)
if(NOT LIB_NCURSES)
	message(FATAL_ERROR "ncursesw not found")
endif()
CHECK_INCLUDE_FILES("ncurses.h" NCURSES_HEADERS_FOUND)
if (NOT NCURSES_HEADERS_FOUND)
	message(FATAL_ERROR "ncurses.h not found")
endif (NOT NCURSES_HEADERS_FOUND)

find_library(LIB_PCRE pcre2-8)
if(NOT LIB_PCRE)
	message(FATAL_ERROR "pcre2-8 not found")
endif()
CHECK_INCLUDE_FILES("pcre_utils.h" PCRE_HEADERS_FOUND)
if (NOT PCRE_HEADERS_FOUND)
	message(STATUS "pcre_utils.h not found")
endif (NOT PCRE_HEADERS_FOUND)

option(DISABLE_UTF "configure --without-UTF" OFF)
# message(STATUS "DISABLE_UTF : ${DISABLE_UTF}")
if (DISABLE_UTF)
	add_definitions(-DDISABLE_UTF)
endif()

add_executable(${EXE_NAME}
	window.c
	pcre_utils.h
	pcre_utils.c
)

target_link_libraries(${EXE_NAME}
	ncursesw
	pcre2-8
)

add_custom_target(allclean
    COMMAND rm -rf ${EXE_NAME} CMakeCache.txt CMakeFiles cmake_install.cmake  Makefile
)