#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_boost_import_variables)

   if(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyBoostIncludePath "/usr/local/include/boost" PARENT_SCOPE)
      set (MyBoostSystemImportPath  "/usr/local/lib/libboost_system.a" PARENT_SCOPE)
      set (MyBoostThreadImportPath  "/usr/local/lib/libboost_thread.a" PARENT_SCOPE)
      set (MySQLite3IncludePath "/usr/include" PARENT_SCOPE)
      set (MySQLite3ImportPath "/usr/lib/arm-linux-gnueabihf/libsqlite3.a" PARENT_SCOPE)
   else()
      set (MyBoostIncludePath "C:/Beagle/boost/include" PARENT_SCOPE)
      set (MyBoostSystemImportPath  "C:/Beagle/boost/lib/libboost_system.a" PARENT_SCOPE)
      set (MyBoostThreadImportPath  "C:/Beagle/boost/lib/libboost_thread.a" PARENT_SCOPE)
      set (MySQLite3IncludePath "C:/Beagle/sqlite3/include" PARENT_SCOPE)
      set (MySQLite3ImportPath  "C:/Beagle/sqlite3/lib/libsqlite3.a" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_boost _target)

   add_library(boost_system STATIC IMPORTED)
   add_library(boost_thread STATIC IMPORTED)

   set_target_properties(boost_system PROPERTIES IMPORTED_LOCATION ${MyBoostSystemImportPath})
   set_target_properties(boost_thread PROPERTIES IMPORTED_LOCATION ${MyBoostThreadImportPath})

   target_link_libraries(${_target} boost_system)
   target_link_libraries(${_target} boost_thread)
   
endfunction()

function(my_inc_import_boost _target)

   target_include_directories(${_target} PUBLIC ${MyBoostIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_sqlite3 _target)

   add_library(sqlite3 STATIC IMPORTED)

   set_target_properties(sqlite3 PROPERTIES IMPORTED_LOCATION ${MySQLite3ImportPath})

   target_link_libraries(${_target} sqlite3)
   
endfunction()

function(my_inc_import_sqlite3 _target)

   target_include_directories(${_target} PUBLIC ${MySQLite3IncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************
