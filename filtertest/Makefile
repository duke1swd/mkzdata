all: gen22 filtertest

filtertest: filtertest.c filter_code.h filter_defines.h filter_test_code.h
	gcc -Wall -o filtertest filtertest.c -lm

filter_test_code.h: gen22
	./gen22

gen22: gen22.c
	gcc -Wall -o gen22 gen22.c -lm
