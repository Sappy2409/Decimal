all: clean s21_decimal.a tostyle clang test leaks gcov_report

s21_decimal.a: clean
	gcc -c -std=c11 -Wall -Werror -Wextra s21_*.c
	ar r s21_decimal.a s21_*.o

test: cleantest
	gcc -std=c11 -Wall -Werror -Wextra -g s21_decimal.a ./s21_tests/s21_*.c -o test -lcheck
	./test

gcov_report: cleantest s21_decimal.a
	gcc -std=c11 -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage s21_decimal.a ./s21_tests/s21_*.c s21_*.c -o tests -lcheck
	./tests
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

leaks: test
	CK_FORK=no leaks --atExit -- ./test

clang:
	clang-format -style=Google -n *.h *.c s21_tests/*.c
	
tostyle:
	clang-format -style=Google -i *.h *.c s21_tests/*.c

clean: cleantest
	rm -rf *.o
	rm -rf *.a

cleantest:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf tests
	rm -rf report
	rm -rf test.dSYM