#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_global_import_variables)

   if(MSVC)
      set (MyRisLibIncludePath "C:/MyTools/MyLib/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/RisLib.lib" PARENT_SCOPE)
      set (MyCisLibIncludePath "C:/MyTools/MyLib/include/CisLib" PARENT_SCOPE)
      set (MyCisLibImportPath  "C:/MyTools/MyLib/lib/CisLib.lib" PARENT_SCOPE)
   elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
      set (MyRisLibIncludePath "/usr/local/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "/usr/local/lib/libRisLib.a" PARENT_SCOPE)
      set (MyCisLibIncludePath "/usr/local/include/CisLib" PARENT_SCOPE)
      set (MyCisLibImportPath  "/usr/local/lib/libCisLib.a" PARENT_SCOPE)
      set (MyPRULibImportPath  "/usr/lib/libprussdrv.a" PARENT_SCOPE)
   else()
      set (MyRisLibIncludePath "C:/MyTools/MyLib/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:/MyTools/MyLib/lib/libRisLib.a" PARENT_SCOPE)
      set (MyCisLibIncludePath "C:/MyTools/MyLib/include/CisLib" PARENT_SCOPE)
      set (MyCisLibImportPath  "C:/MyTools/MyLib/lib/libCisLib.a" PARENT_SCOPE)
      set (MyPRULibImportPath  "C:/Beagle/toolchain/arm-linux-gnueabihf/libc/usr/lib/libprussdrv.a" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   add_library(RisLib STATIC IMPORTED)

   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})

   if (MSVC)
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
   else()
      if (CMAKE_SYSTEM_VERSION EQUAL 101)
         set (MyPThreadImportPath  "C:/Beagle/toolchain/arm-linux-gnueabihf/libc/usr/lib/libpthread.so")
      else()
         set (MyPThreadImportPath  "/usr/lib/arm-linux-gnueabihf/libpthread.so")
      endif()
      add_library(PThreadLib SHARED IMPORTED)
      set_target_properties(PThreadLib PROPERTIES IMPORTED_LOCATION ${MyPThreadImportPath})
      target_link_libraries(RisLib INTERFACE PThreadLib)
   endif()

   target_link_libraries(${_target} RisLib)
   
endfunction()

function(my_inc_import_RisLib _target)

   target_include_directories(${_target} PUBLIC ${MyRisLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_CisLib _target)

   add_library(CisLib STATIC IMPORTED)
   set_target_properties(CisLib PROPERTIES IMPORTED_LOCATION ${MyCisLibImportPath})

   target_link_libraries(${_target} CisLib)

endfunction()

function(my_inc_import_CisLib _target)

   target_include_directories(${_target} PUBLIC ${MyCisLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_PRULib _target)

   add_library(PRULib STATIC IMPORTED)
   set_target_properties(PRULib PROPERTIES IMPORTED_LOCATION ${MyPRULibImportPath})

   target_link_libraries(${_target} PRULib)

endfunction()

