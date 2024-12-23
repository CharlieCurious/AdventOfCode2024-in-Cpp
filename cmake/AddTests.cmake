function(addTests dayName)
    add_subdirectory("${CMAKE_SOURCE_DIR}/external/boost_ut" "${CMAKE_BINARY_DIR}/external/boost_ut")

    file(GLOB TEST_SRCS "${CMAKE_SOURCE_DIR}/solutions/${dayName}/tests/*.cpp")

    # Check if ${dayName}_lib exists
    set(day_lib_exists OFF)
    if (TARGET ${dayName}_lib)
        set(day_lib_exists ON)
    endif()

    set(TEST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/tests")

    foreach(testFile ${TEST_SRCS})
        # Extract file name without the extension
        get_filename_component(testName ${testFile} NAME_WE)

        add_executable(${testName} ${testFile})
        target_compile_options(${testName} PRIVATE -Wall -Wextra -g)
        set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR})

        if (day_lib_exists)
            target_link_libraries(${testName} PRIVATE ut ${dayName}_lib)
        else()
            target_link_libraries(${testName} PRIVATE ut)
        endif()

        add_test(NAME ${testName} COMMAND ${testName})
    endforeach()

endfunction()
