rm -f *.gcda && \
g++ -O0 --coverage tests/test_logictool.cpp src/logictool.cpp -o run_tests -lgtest -lgtest_main -pthread && \
./run_tests && \
lcov --capture --directory . --output-file coverage.info --quiet && \
lcov --remove coverage.info '/usr/*' '*/gtest/*' --output-file coverage.info && \
lcov --summary coverage.info
rm -f *.gcda && \
rm -f *.gcno
