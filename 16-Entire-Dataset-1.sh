source "${TEST_DIR}/lib/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; \
    ${TEST_DIR}/lib/das ./ | sort)

test_start "Checks the output against the entire test dataset"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da -s . | sort)

compare_outputs

test_end
