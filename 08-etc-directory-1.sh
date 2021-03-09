source "${TEST_DIR}/lib/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/lib/das ./etc | sort)

test_start "Checks the output against the test etc directory"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da ./etc | sort)

compare_outputs

test_end
