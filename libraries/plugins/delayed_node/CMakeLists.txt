file(GLOB HEADERS "include/evolution/delayed_node/*.hpp")

add_library( evolution_delayed_node 
             delayed_node_plugin.cpp
           )

target_link_libraries( evolution_delayed_node evolution_chain evolution_app )
target_include_directories( evolution_delayed_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( delayed_node_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   evolution_delayed_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
