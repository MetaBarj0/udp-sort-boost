if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type. Valid values are: Debug, Release, MinSizeRel, RelWithDebInfo" FORCE)
endif()
