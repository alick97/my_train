add_executable(byteorder byteorder.c)
set_target_properties(byteorder PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(byteorder PRIVATE tutorial_common)
