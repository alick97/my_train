add_library(MathFunctions
            mysqrt.cxx
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

target_include_directories(MathFunctions
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)

# include(CheckSymbolExists)
# set(CMAKE_REQUIRED_LIBRARIES "m")
# check_symbol_exists(log "math.h" HAVE_LOG)
# check_symbol_exists(exp "math.h" HAVE_EXP)

# if (HAVE_EXP AND HAVE_LOG)
#     target_compile_definitions(MathFunctions
#                                PRIVATE "HAVE_LOG" "HAVE_EXP")
# endif()

add_executable(MakeTable MakeTable.cxx)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        DEPENDS MakeTable
)
