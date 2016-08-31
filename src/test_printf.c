/*
 * File:   test_printf.c
 * Author: gouarfig
 *
 * Created on 21 April 2015, 21:49
 */

#include <stdio.h>
#include <stdlib.h>

/*
 *
 */
int main(int argc, char** argv) {
	printf("|%-*s|\n", 20, "test");
	return (EXIT_SUCCESS);
}

