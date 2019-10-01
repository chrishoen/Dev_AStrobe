#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_boost_import_variables)

   if(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyBoostIncludePath "/usr/local/include/boost" PARENT_SCOPE)
      set (MyBoostSystemImportPath  "/usr/local/lib/libboost_system.a" PARENT_SCOPE)
      set (MyBoostThreadImportPath  "/usr/local/lib/libboost_thread.a" PARENT_SCOPE)
   else()
      set (MyBoostIncludePath "C:/Beagle/boost/include" PARENT_SCOPE)
      set (MyBoostSystemImportPath  "C:/Beagle/boost/lib/libboost_system.a" PARENT_SCOPE)
      set (MyBoostThhreadImportPath  "C:/Beagle/boost/lib/libboost_thread.a" PARENT_SCOPE)
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
