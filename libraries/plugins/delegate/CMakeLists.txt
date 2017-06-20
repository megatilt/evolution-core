file(GLOB HEADERS "include/evolution/delegate/*.hpp")

add_library( evolution_delegate 
             delegate.cpp
           )

target_link_libraries( evolution_delegate evolution_chain evolution_app )
target_include_directories( evolution_delegate
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   evolution_delegate

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
