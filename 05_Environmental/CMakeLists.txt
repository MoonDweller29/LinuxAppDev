cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME pcre_gui)
set(EXE_NAME pcre_demo)
project (${PROJECT_NAME})

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -Wall)

find_library(LIB_NCURSES ncursesw)
if(NOT LIB_NCURSES)
	message(FATAL_ERROR "ncursesw not found")
endif()
find_library(LIB_PCRE pcre2-8)
if(NOT LIB_PCRE)
	message(FATAL_ERROR "pcre2-8 not found")
endif()
# message(STATUS "LEL : ${LIB_NCURSES}")

add_executable(${EXE_NAME}
	window.c
	pcre_utils.h
	pcre_utils.c
)

target_link_libraries(${EXE_NAME}
	ncursesw
	pcre2-8
)