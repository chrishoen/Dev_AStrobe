cmake_minimum_required (VERSION 3.8)
#change1
set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)
include(MySpecial.cmake)

project ("Dev_AStrobe")
my_init_global_import_variables()

my_special1()

add_subdirectory ("CommonLib")
add_subdirectory ("astrobe")
add_subdirectory ("Test")
return()

