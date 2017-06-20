file(GLOB HEADERS "include/evolution/account_history/*.hpp")

add_library( evolution_account_history 
             account_history_plugin.cpp
           )

target_link_libraries( evolution_account_history evolution_chain evolution_app )
target_include_directories( evolution_account_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( account_history_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   evolution_account_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/evolution/account_history" )

