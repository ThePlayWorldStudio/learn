g++ -O0 --coverage tests/test_logictool.cpp src/logictool.cpp -o run_tests -lgtest -lgtest_main -pthread
./run_tests
lcov --remove coverage.info '*/gtest/*' '*/test_logictool.cpp' --output-file coverage.info
