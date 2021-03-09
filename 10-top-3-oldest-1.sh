source "${TEST_DIR}/lib/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; \
    ${TEST_DIR}/lib/das ./etc age | tail -n 3 | sort)

test_start "Checks the output against the test etc directory, limited to 3 lines sorted by oldest"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da -a -l 3 ./etc | sort)

compare_outputs

test_end
