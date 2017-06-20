file(GLOB HEADERS "include/evolution/db/*.hpp")
add_library( evolution_db undo_database.cpp index.cpp object_database.cpp ${HEADERS} )
target_link_libraries( evolution_db fc )
target_include_directories( evolution_db PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   evolution_db

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/evolution/db" )
