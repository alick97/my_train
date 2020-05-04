add_executable(daytime_client daytime_client.c)
set_target_properties(daytime_client PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(daytime_client PRIVATE tutorial_common)


add_executable(daytime_server daytime_server.c)
set_target_properties(daytime_server PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(daytime_server PRIVATE tutorial_common)
