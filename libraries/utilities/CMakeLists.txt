list( APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libraries/fc/GitVersionGen" )
include( GetGitRevisionDescription )
get_git_head_revision(GIT_REFSPEC EVOLUTION_GIT_REVISION_SHA)
get_git_unix_timestamp(EVOLUTION_GIT_REVISION_UNIX_TIMESTAMP)
git_describe(EVOLUTION_GIT_REVISION_DESCRIPTION --tags)
if(NOT EVOLUTION_GIT_REVISION_DESCRIPTION)
    set(EVOLUTION_GIT_REVISION_DESCRIPTION "unknown")
endif(NOT EVOLUTION_GIT_REVISION_DESCRIPTION)

file(GLOB HEADERS "include/evolution/utilities/*.hpp")

set(sources
   key_conversion.cpp
   string_escape.cpp
   tempdir.cpp
   words.cpp
   ${HEADERS})

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/git_revision.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp" @ONLY)
list(APPEND sources "${CMAKE_CURRENT_BINARY_DIR}/git_revision.cpp")

add_library( evolution_utilities
             ${sources}
             ${HEADERS} )
target_link_libraries( evolution_utilities fc )
target_include_directories( evolution_utilities
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
if (USE_PCH)
  set_target_properties(evolution_utilities PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
  cotire(evolution_utilities)
endif(USE_PCH)

install( TARGETS
   evolution_utilities

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/evolution/utilities" )
