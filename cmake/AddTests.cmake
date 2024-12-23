function(addTests dayName)
    add_subdirectory("${CMAKE_SOURCE_DIR}/external/boost_ut" "${CMAKE_BINARY_DIR}/external/boost_ut")

    file(GLOB TEST_SRCS "${CMAKE_SOURCE_DIR}/solutions/${dayName}/tests/*.cpp")

    set(TEST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/tests")

    foreach(testFile ${TEST_SRCS})
        # Extract file name without the extension
        get_filename_component(testName ${testFile} NAME_WE)

        add_executable(${testName} ${testFile})
        target_link_libraries(${testName} PRIVATE ut)

        set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR})

        add_test(NAME ${testName} COMMAND ${testName})
    endforeach()

endfunction()
