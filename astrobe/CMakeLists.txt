﻿cmake_minimum_required (VERSION 3.8)

project (astrobe CXX)
my_find_src_files (src_files astrobe)
add_executable (astrobe ${src_files})
my_add_compile_options (astrobe)
my_add_pch (astrobe)

my_inc_import_CommonLib(astrobe)
my_inc_import_RisLib(astrobe)

my_lib_import_CommonLib(astrobe)
my_lib_import_RisLib(astrobe)

target_link_options(astrobe PUBLIC "-lpthread")


if(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(TARGETS astrobe DESTINATION "/opt/prime/bin")
else()
   add_custom_command(
      TARGET  astrobe
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx astrobe rsync://debian@bbx/prime/bin
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_AStrobe/astrobe)
endif()
