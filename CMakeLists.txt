project (DICE_ROLL)
cmake_minimum_required (VERSION 2.8)

find_package (PkgConfig REQUIRED)

# Use GLib
pkg_check_modules (GLIB REQUIRED glib-2.0)
include_directories (${GLIB_INCLUDE_DIRS})
link_directories (${GLIB_LIBRARY_DIRS})

# Use math lib
find_library (M_LIB m)

add_executable (roll
	main.c
	die.c)
add_definitions (${GLIB_CFLAGS_OTHER} -g -Wall)
target_link_libraries (roll ${GLIB_LIBRARIES} ${M_LIB})

