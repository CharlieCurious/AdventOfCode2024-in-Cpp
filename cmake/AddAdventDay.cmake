include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/AddTests.cmake)

function(addAdventDay dayName)
    set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${dayName}/src")
    file(GLOB SOURCES "${SRC_DIR}/*.cpp")

    # Separate main.cpp from other source files in order to create a lib and an executable.
    set(MAIN_FILE "")
    set(LIB_FILES "")

    foreach(file ${SOURCES})
        get_filename_component(filename ${file} NAME)
        if(filename STREQUAL "main.cpp")
            set(MAIN_FILE ${file})
        else()
            list(APPEND LIB_FILES ${file})
        endif()
    endforeach()

    set(SANITIZERS -fsanitize=address -fsanitize=undefined -no-pie) # Optionally add this.
    set(COMPILER_FLAGS -Wall -Wextra -g)

    # If there are lib files, create a static library with all source files except main.cpp
    if (LIB_FILES)
        set(LIB "${dayName}_lib")
        add_library(${LIB} STATIC ${LIB_FILES})
        target_compile_options(${LIB} PRIVATE ${COMPILER_FLAGS})
        target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${dayName}/include)
        set(LINK_LIBS ${LIB})
    else()
        set(LINK_LIBS)
    endif()

    add_executable(${dayName} ${MAIN_FILE})

    target_link_libraries(${dayName} PRIVATE ${LINK_LIBS})
    target_include_directories(${dayName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${dayName}/include)
    target_compile_options(${dayName} PRIVATE ${COMPILER_FLAGS})

    if (ENABLE_TESTS)
        addTests(${dayName})
    endif()
endfunction()
