﻿cmake_minimum_required (VERSION 3.8)

project (Experiment CXX)

my_find_src_files (src_files Experiment)
add_executable (Experiment ${src_files})
my_add_compile_options (Experiment)
my_add_pch (Experiment)


my_inc_import_RisLib(Experiment)
my_inc_import_boost(Experiment)
my_inc_import_sqlite3(Experiment)

my_lib_import_RisLib(Experiment)
my_lib_import_boost(Experiment)
my_lib_import_stdfs(Experiment)
my_lib_import_sqlite3(Experiment)

return()

if(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(TARGETS Experiment DESTINATION "/opt/prime/bin")
else()
   add_custom_command(
      TARGET  Experiment
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx Experiment rsync://debian@bbx/prime/bin
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_AStrobe/Experiment)
endif()
