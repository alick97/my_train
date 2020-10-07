add_library(tutorial_common
            error.c
            wrapsocket.c
            sock_bind_wild.c)
set_property(TARGET tutorial_common PROPERTY VERSION "1.0.0")
set_property(TARGET tutorial_common PROPERTY SOVERSION "1")

# state that anybody linking to us needs to include the current source dir
# to find header file, while we don't.
target_include_directories(tutorial_common
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           "${PROJECT_BINARY_DIR}"
                           )
