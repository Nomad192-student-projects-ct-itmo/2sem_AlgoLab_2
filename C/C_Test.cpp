#include "AlmostTree.h"
#include "TestTree.h"
#include "C_Test.h"

bool test(class AVL &tree)
{
	std::stringstream tree_output;
	tree.full_print_stream(tree_output);

	size_t n;
	tree_output >> n;
	TestTree test_tree(n);

	for (size_t i = 0; i < n; i++)
	{
		TREE_TYPE x;
		size_t l, r;
		tree_output >> x >> l >> r;
		if((l != -1 && r != -1) && l >= r)
			return false; 
		test_tree.add(TestTree::Node{x, --l, --r});
	}
	size_t root;
	tree_output >> root;
	return test_tree.isTree(--root);
}

struct Req
{
	enum Type
	{
		INSERT,
		DELETE,
		EXISTS,
		NEXT,
		PREV,  
	};
	Type type;
	TREE_TYPE x;

	Req() : type(INSERT), x(0) {}
	Req(Type type, TREE_TYPE x) : type(type), x(x) {}
};

static void print_error(const char *error_str, size_t length, Req *req_arr, AVL *tree)
{
	printf("Error %s with data:\n", error_str);
	printf("len op = %d\n", length);
	for (size_t i = 0; i < length; i++)
	{
		printf("%u %u\n", req_arr[i].type, req_arr[i].x);
	}
	printf("\nAVL full print stream:\n");
	tree->full_print_stream(std::cout);
	printf("\n\nAVL full print:\n");
	tree->full_print();
}

bool full_test()
{
	printf("len test, range: 1 - %u, n tests = %d\n", TEST_LEN_OP, N_TEST);
	Req *req_arr = new Req[TEST_LEN_OP];

	for (size_t length = 1; length <= TEST_LEN_OP; length++)
    {
    	if((length-1) % (TEST_LEN_OP/N_TEST_POINT) == 0)
    		printf("	len test %g%%\n", ((double)(length-1) / (double)TEST_LEN_OP) * 100);

    	for(size_t n_attempt = 0; n_attempt < N_TEST; n_attempt++)
        {
        	AVL tree;
        	AlmostTree test_tree;

        	for(size_t i = 0; i < length; i++)
        	{						//Req::Type(rand() % 5)
        		req_arr[i] = Req(Req::Type(0), (rand() % RANGE_VAL) + OFFSET_VAL);
        		switch(req_arr[i].type)
        		{
        			case Req::Type::INSERT: 
        			{
        				bool res 		= tree.insert		(req_arr[i].x); 
        				bool res_test 	= test_tree.insert	(req_arr[i].x); 
        				if(res != res_test)
        				{
							print_error("insert", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
        			}
        			//case Req::Type::EXISTS: {}
        		}
        	}
        	if(!test(tree))
	    	{
				print_error("tree", length, req_arr, &tree);
				delete[] req_arr;
				return false;
	    	}
    	}
    }
    delete[] req_arr;
    printf("	len test 100%% - OK\n");
    return true;
}