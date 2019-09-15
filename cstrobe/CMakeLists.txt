cmake_minimum_required (VERSION 3.8)

project (cstrobe CXX)
my_find_src_files (src_files cstrobe)
add_executable (cstrobe ${src_files})
my_add_compile_options (cstrobe)
my_add_pch (cstrobe)

my_inc_import_CommonLib(cstrobe)
my_inc_import_RisLib(cstrobe)

my_lib_import_CommonLib(cstrobe)
my_lib_import_RisLib(cstrobe)
my_lib_import_PRULib(cstrobe)

if (MSVC)
   install(TARGETS cstrobe DESTINATION "C:\\aaa_cproc\\bin")
elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(TARGETS cstrobe DESTINATION "/opt/cproc/bin")
else()
   add_custom_command(
      TARGET  cstrobe
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx cstrobe rsync://debian@bbx/cproc/bin
      WORKING_DIRECTORY C:/Users/chris/CMakeBuilds/Dev_CStrobe/cstrobe)
endif()
