source "${TEST_DIR}/lib/funcs.bash"

run_timeout=10

reference_output=$(${TEST_DIR}/lib/das "${TEST_DIR}/inputs/test-fs/etc" | sort)

test_start "Checks the output against the test etc directory"

program_output=$(./da "${TEST_DIR}/inputs/test-fs/etc" | sort)

compare_outputs

test_end
