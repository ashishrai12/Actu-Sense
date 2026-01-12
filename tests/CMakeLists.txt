include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee9d7daed034743e0ceb2da0c624a1ee.zip
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ActuSenseTests
    test_sensor.cpp
    test_environment.cpp
)

target_link_libraries(ActuSenseTests
    PRIVATE
        ActuSenseLib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ActuSenseTests)
