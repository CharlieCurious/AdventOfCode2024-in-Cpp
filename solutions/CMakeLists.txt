if(DAY)
    addAdventDay("${DAY}")
else()
    message(FATAL_ERROR "DAY is not set or invalid.")
endif()

