file(GLOB HEADERS "include/evolution/debug_delegate/*.hpp")

add_library( evolution_debug_delegate
             debug_api.cpp
             debug_delegate.cpp
           )

target_link_libraries( evolution_debug_delegate evolution_chain evolution_app )
target_include_directories( evolution_debug_delegate
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   evolution_debug_delegate

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
