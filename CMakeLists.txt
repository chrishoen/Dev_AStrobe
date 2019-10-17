cmake_minimum_required (VERSION 3.8)
#change1
set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)
include(MyBoostImports.cmake)

project ("Dev_AStrobe")
my_init_global_import_variables()
my_init_boost_import_variables()

add_subdirectory ("CommonLib")
add_subdirectory ("astrobe")
add_subdirectory ("Experiment")
add_subdirectory ("Test")
return()

add_subdirectory ("Test")
return()

add_subdirectory ("CommonLib")
add_subdirectory ("astrobe")
add_subdirectory ("Experiment")
add_subdirectory ("Test")
return()

add_subdirectory ("Experiment")
return()

