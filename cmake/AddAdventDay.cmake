function(addAdventDay dayName)
    set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${dayName}/src")
    file(GLOB SOURCES "${SRC_DIR}/*.cpp")

    add_executable(${dayName} ${SOURCES})

    target_include_directories(${dayName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${dayName}/include)
    target_compile_options(${dayName} PRIVATE -Wall -Wextra -O2 -g)
endfunction()
