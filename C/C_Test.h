#ifndef C_TEST_H
#define C_TEST_H

#include <sstream>
#include <cstdlib>
#include <cstdio>

#include "AVL.h"

#define MIN(x, y) ((x < y) ? (x) : (y))
#define MAX(x, y) ((x > y) ? (x) : (y))

#define TEST_LEN_OP 	(2000)	//10
#define N_TEST 			(100)	//1000000
#define N_TEST_POINT 	MIN((1000), 	TEST_LEN_OP)
#define RANGE_VAL 		MAX((2000000000), 	TEST_LEN_OP)	//1000000000
#define OFFSET_VAL 		(-1000000000)

bool test(class AVL &tree);
bool full_test();

#endif