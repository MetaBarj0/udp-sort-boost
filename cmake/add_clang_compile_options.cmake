if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  return()
endif()

add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
  -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion
  -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  return()
endif()

add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=undefined)

# unsupported on windows platforms
if(WIN32)
  return()
endif()

add_compile_options(-fsanitize=safe-stack)
add_link_options(-fsanitize=safe-stack)
