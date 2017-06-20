add_executable( delegate_node main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling delegate_node with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

# We have to link against evolution_debug_delegate because deficiency in our API infrastructure doesn't allow plugins to be fully abstracted #246
target_link_libraries( delegate_node
                       PRIVATE evolution_app evolution_account_history evolution_market_history evolution_delegate evolution_chain evolution_debug_delegate evolution_egenesis_full fc ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} )

install( TARGETS
   delegate_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
