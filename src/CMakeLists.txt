find_package(Boost REQUIRED COMPONENTS system)
find_package(fmt REQUIRED)

set(UdpSortServer_sources "server.cpp")
set(UdpSortClient_sources "client.cpp")

add_executable(UdpSortServer ${UdpSortServer_sources})
add_executable(UdpSortClient ${UdpSortClient_sources})

target_compile_features(UdpSortServer PRIVATE cxx_std_23)
target_compile_features(UdpSortClient PRIVATE cxx_std_23)

# provide a function to create sanitized target and expose their names in the
# specified target properties
include(../cmake/create_clang_sanitize_targets.cmake)

target_link_libraries(UdpSortServer PRIVATE Boost::system fmt::fmt)
target_link_libraries(UdpSortClient PRIVATE Boost::system fmt::fmt)

if(WIN32)
  target_link_libraries(UdpSortServer PRIVATE ws2_32)
  target_link_libraries(UdpSortClient PRIVATE ws2_32)
endif()

create_clang_sanitize_targets(UdpSortServer ${UdpSortServer_sources})
create_clang_sanitize_targets(UdpSortClient ${UdpSortClient_sources})

