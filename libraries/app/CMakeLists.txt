file(GLOB HEADERS "include/evolution/app/*.hpp")
file(GLOB EGENESIS_HEADERS "../egenesis/include/evolution/app/*.hpp")

add_library( evolution_app 
             api.cpp
             application.cpp
             database_api.cpp
             impacted.cpp
             plugin.cpp
             ${HEADERS}
             ${EGENESIS_HEADERS}
           )

# need to link evolution_debug_delegate because plugins aren't sufficiently isolated #246
target_link_libraries( evolution_app evolution_market_history evolution_account_history evolution_chain fc evolution_db evolution_net evolution_utilities evolution_debug_delegate )
target_include_directories( evolution_app
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
                            "${CMAKE_CURRENT_SOURCE_DIR}/../egenesis/include" )

if(MSVC)
  set_source_files_properties( application.cpp api.cpp database_api.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   evolution_app

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/evolution/app" )
