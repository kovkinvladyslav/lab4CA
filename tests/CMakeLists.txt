include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(INTEGRATION_TEST_SOURCES
    integration/IntegrationTests.cpp
)

set(INSTRUCTIONS_TEST_SOURCES
    instructions/ComplexInstructionTests.cpp
    instructions/SingleInstructionTests.cpp
)

add_executable(IntegrationTest ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${INTEGRATION_TEST_SOURCES})
target_link_libraries(IntegrationTest ${LIB_NAME} GTest::gtest_main )
target_include_directories(IntegrationTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/ ${CMAKE_CURRENT_SOURCE_DIR}/utils/)

add_executable(InstructionsTest ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${INSTRUCTIONS_TEST_SOURCES})
target_link_libraries(InstructionsTest ${LIB_NAME} GTest::gtest_main)
target_include_directories(InstructionsTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/ ${CMAKE_CURRENT_SOURCE_DIR}/utils/)

add_test(IntegrationTest_gtests IntegrationTest)
add_test(InstructionsTest_gtests InstructionsTest)
