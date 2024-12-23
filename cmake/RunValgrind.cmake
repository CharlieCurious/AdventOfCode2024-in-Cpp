function(runValgrind dayName)
    add_custom_command(TARGET ${dayName} POST_BUILD
        COMMAND valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes $<TARGET_FILE:${dayName}>
        COMMENT "Running Valgrind to check for memory leaks for ${dayName}")
endfunction()
