#ifndef C_TEST_H
#define C_TEST_H

#include <sstream>
#include <cstdlib>
#include <cstdio>

#include "AVL.h"

#define MIN(x, y) ((x < y) ? (x) : (y))

#define TEST_LEN_OP (20)	//10
#define N_TEST (1000)	//1000000
#define N_TEST_POINT MIN((10), TEST_LEN_OP)
#define RANGE_VAL (100)	//1000000000
#define OFFSET_VAL (1)

bool test(class AVL &tree);
bool full_test();

#endif