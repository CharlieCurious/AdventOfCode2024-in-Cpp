#!/bin/bash

CYAN="\033[36m"
BOLD="\033[1m"
RESET="\033[0m"

if [ $# -lt 1 ]; then
    echo "Usage: $0 <path_to_executable> [--tool memcheck|cache]"
    exit 1
fi

EXECUTABLE=$1
TOOL=${2:-all}

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: executable '$EXECUTABLE' not found."
    exit 1
fi

run_memcheck() {
    echo -e "${CYAN}${BOLD}=== Running Memcheck on '${EXECUTABLE}' ===${RESET}"
    valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes "$EXECUTABLE"
}

run_cachegrind() {
    echo -e "${CYAN}${BOLD}=== Running Cachegrind on '${EXECUTABLE}' ===${RESET}"
    valgrind --tool=cachegrind --cachegrind-out-file=/dev/null "$EXECUTABLE"
}

check_execution_time() {
    echo -e "${CYAN}${BOLD}=== Measuring execution time of '${EXECUTABLE}' ===${RESET}"
    start_time=$(date +%s%N)

    "$EXECUTABLE"

    # Get the end time in nanoseconds
    end_time=$(date +%s%N)

    execution_time=$((end_time - start_time))
    seconds=$((execution_time / 1000000000))
    nanoseconds=$((execution_time % 1000000000))

    echo -e "Execution time: ${seconds}.${nanoseconds} seconds"
}

case $TOOL in
    memcheck)
        run_memcheck
        ;;
    cache)
        run_cachegrind
        ;;
    time)
        check_execution_time
        ;;
    all)
        run_memcheck
        run_cachegrind
        check_execution_time
        ;;
    *)
        echo "Invalid tool: $TOOL"
        echo "Valid options are: --tool memcheck, --tool cache, --tool time, or leave empty for all."
        exit 1
        ;;
esac
