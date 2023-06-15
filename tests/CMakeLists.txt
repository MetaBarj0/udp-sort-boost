find_package(Catch2 3.3.2 REQUIRED)

set(Tests_sources test.cpp)

# TODO: iterate through all production code targets and create test suites
# accordingly. There should be one normal production code target and at least
# one sanitized production code target.
# Production code sanitized target name list can be found in the
# `SanitizeTargetNames` property of the base target used to create sanitize
# targets. The base target is the first argument provided in the
# `create_clang_sanitize_targets` function call.
# Below is a very trivial example of one test target you can inspire yourself
# with. It does not iterate at all but may define what will be inside the loop.
#
# get_property(property TARGET VulkanTutorial PROPERTY SanitizeTargetNames)
# message("fancy target property: ${property}")

add_executable(Tests ${Tests_sources})
target_compile_features(Tests PRIVATE cxx_std_23)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(Tests)
