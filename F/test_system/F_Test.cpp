#include "AlmostTree.hpp"
#include "TestTree.hpp"
#include "F_Test.hpp"
#include <ctime>

static bool testIsTree(class AVL &tree)
{
	std::stringstream tree_output;
	tree.print_stream(tree_output);

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
		DEL,
		EXISTS,
		NEXT,
		PREV, 
		SUM, 		
	};
	Type type;
	TREE_TYPE x;
	TREE_TYPE y;

	Req() : type(INSERT), x(0), y(0) {}
	Req(Type type, TREE_TYPE x) : type(type), x(x), y(0) {}
	Req(Type type, TREE_TYPE x, TREE_TYPE y) : type(type), x(x), y(y) {}
};

static void print_error(const char *error_str, size_t length, Req *req_arr, AVL *tree)
{
	printf("Error %s with data:\n", error_str);
	printf("len op = %d\n", length);
	for (size_t i = 0; i < length; i++)
	{
		printf("%d %" TREE_TYPE_SP " %" TREE_TYPE_SP "\n", req_arr[i].type, req_arr[i].x, req_arr[i].y);
	}
	printf("\nAVL full print stream:\n");
	tree->print_stream(std::cout);
	printf("\n\nAVL full print:\n");
	tree->full_print();

	printf("\n\noperations:\n");
	for(size_t i = 0; i < length; i++)
    {
    	switch(req_arr[i].type)
        {
			case Req::Type::INSERT:
			{
				printf("insert %" TREE_TYPE_SP "\n", req_arr[i].x);
				break;
			}
			case Req::Type::DEL:
			{
				printf("delete %u\n", req_arr[i].x);
				break;
			}
			case Req::Type::EXISTS:
			{
				printf("exists %u\n", req_arr[i].x);
				break;
			}
			case Req::Type::NEXT:
			{
				printf("next %u\n", req_arr[i].x);
				break;
			}
			case Req::Type::PREV:
			{
				printf("prev %u\n", req_arr[i].x);
				break;
			}
			case Req::Type::SUM:
			{
				printf("sum %" TREE_TYPE_SP " %" TREE_TYPE_SP "\n", req_arr[i].x, req_arr[i].y);
				break;
			}
		}	
    }

    printf("\n\nTrace:\n");
    AVL trace;

	for(size_t i = 0; i < length; i++)
    {	
   		switch(req_arr[i].type)
        {
			case Req::Type::INSERT:
			{
				printf("insert %" TREE_TYPE_SP "\n", req_arr[i].x);
                trace.insert(req_arr[i].x);
				break;
			}
			case  Req::Type::DEL:
			{
				printf("delete %u\n", req_arr[i].x);
                trace.del(req_arr[i].x);
				break;
			}
			case Req::Type::EXISTS:
			{
				printf("exists %u\n", req_arr[i].x);
                trace.exists(req_arr[i].x);
				break;
			}
			case Req::Type::NEXT:
			{
				printf("next %u\n", req_arr[i].x);
				TREE_TYPE res_x;
                if(trace.next(req_arr[i].x, &res_x))
					printf("%" TREE_TYPE_SP "\n", res_x);
				else
					printf("none\n");
				break;
			}
			case Req::Type::PREV:
			{
				printf("prev %u\n", req_arr[i].x);
				TREE_TYPE res_x;
                if(trace.prev(req_arr[i].x, &res_x))
					printf("%" TREE_TYPE_SP "\n", res_x);
				else
					printf("none\n");
				break;
			}			
			case  Req::Type::SUM:
			{
				printf("sum %" TREE_TYPE_SP " %" TREE_TYPE_SP "\n", req_arr[i].x, req_arr[i].y);
				printf("%" TREE_TYPE_SP "\n", trace.sum(req_arr[i].x, req_arr[i].y));
				break;
			}
		}
		trace.full_print();
	}	
}

static void update_loadbar(size_t length, size_t n_attempt)
{
	printf("\b\b\b\b\b\b%4.1f%%]", ((double)(length-1)*(N_TEST) + n_attempt) / ((double)TEST_LEN_OP*(N_TEST)) * 100);
}

bool full_test()
{
	printf("len test, range: [%u - %u], n tests = %d for each value from the range.\n", OFFSET_LEN_OP, TEST_LEN_OP + OFFSET_LEN_OP - 1, N_TEST);
	Req *req_arr = new Req[OFFSET_LEN_OP + TEST_LEN_OP];
	int start = clock();
	int all = start;
	printf("\tlen test [   0%]");
	for (size_t length = OFFSET_LEN_OP; length < TEST_LEN_OP + OFFSET_LEN_OP; length++)
    {

    	for(size_t n_attempt = 0; n_attempt < N_TEST; n_attempt++)
        {
        	int end = clock();
	    	if(((length-1)*N_TEST + n_attempt) % (TEST_LEN_OP*N_TEST/N_TEST_POINT) == 0 && end - start >= 500)
	    	{
	    		start = clock();
	    		update_loadbar(length, n_attempt);
	    	}

        	AVL tree;
        	AlmostTree test_tree;

        	for(size_t i = 0; i < length; i++)
        	{
        		//if(i%(length/100) == 0) printf("%zu\n", i/(length/100));

        		req_arr[i] = Req(Req::Type(rand() % 2 ? Req::Type::INSERT : Req::Type::SUM), (rand() % RANGE_VAL) + OFFSET_VAL);
        		switch(req_arr[i].type)
        		{
        			case Req::Type::INSERT: 
        			{
        				bool res 		= tree.insert		(req_arr[i].x); 
        				bool res_test 	= test_tree.insert	(req_arr[i].x); 
        				if(res != res_test)
        				{
        					update_loadbar(length, n_attempt);
        					printf("\ttree = %d, test = %d\n", res, res_test);        					
							print_error("insert", i+1, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
        			}
        			case Req::Type::DEL:
        			{
        				bool res 		= tree.del			(req_arr[i].x); 
        				bool res_test 	= test_tree.del 	(req_arr[i].x);
        				if(res != res_test)
        				{
        					printf("\ttree = %d, test = %d\n", res, res_test);
							print_error("delete", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
       				}
        			case Req::Type::EXISTS: 
					{    				
        				bool res 		= tree.exists		(req_arr[i].x); 
        				bool res_test 	= test_tree.exists 	(req_arr[i].x);
        				if(res != res_test)
        				{
        					printf("\ttree = %d, test = %d\n", res, res_test);        				
							print_error("exists", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
        			}
        			case Req::Type::NEXT: 
					{    				
						TREE_TYPE res_x;
						TREE_TYPE res_test_x;
        				bool res 		= tree.next			(req_arr[i].x, &res_x); 
        				bool res_test 	= test_tree.next 	(req_arr[i].x, &res_test_x);
        				if(res != res_test)
        				{
        					printf("\ttree = %d, test = %d\n", res, res_test);        				
							print_error("exists", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				if(res && (res_x != res_test_x))
        				{
        					printf("\ttree = %" TREE_TYPE_SP", test = %" TREE_TYPE_SP"\n", res_x, res_test_x);        				
							print_error("exists", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
        			}
        			case Req::Type::PREV: 
					{    				
						TREE_TYPE res_x;
						TREE_TYPE res_test_x;
        				bool res 		= tree.prev			(req_arr[i].x, &res_x); 
        				bool res_test 	= test_tree.prev 	(req_arr[i].x, &res_test_x);
        				if(res != res_test)
        				{
        					printf("\ttree = %d, test = %d\n", res, res_test);        				
							print_error("exists", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				if(res && (res_x != res_test_x))
        				{
        					printf("\ttree = %" TREE_TYPE_SP", test = %" TREE_TYPE_SP"\n", res_x, res_test_x);        				
							print_error("exists", length, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
        			}
        			case Req::Type::SUM:
        			{
        				req_arr[i].y = (rand() % RANGE_VAL) + OFFSET_VAL;
        				TREE_TYPE_SUM res 		= tree.sum			(req_arr[i].x, req_arr[i].y); 
        				TREE_TYPE_SUM res_test 	= test_tree.sum 	(req_arr[i].x, req_arr[i].y);
        				if(res != res_test)
        				{
        					update_loadbar(length, n_attempt);
        					printf("\ttree = %" TREE_TYPE_SUM_SP ", test = %" TREE_TYPE_SUM_SP "\n", res, res_test);
							print_error("sum", i+1, req_arr, &tree);
							delete[] req_arr;
							return false;
        				}
        				break;
       				}
        		}
	        	/*if(!testIsTree(tree))
		    	{
					print_error("tree", i+1, req_arr, &tree);
					delete[] req_arr;
					return false;
		    	}*/
        	}
			/*if(!testIsTree(tree))
	    	{
				print_error("tree", i+1, req_arr, &tree);
				delete[] req_arr;
				return false;
	    	}*/
    	}
    }
    delete[] req_arr;
    printf("\b\b\b\b\b\b100%%] - OK\n");
    float t = clock();
    t -= all;
    t /= 1000;
    printf("Time: %gs\n", t);
    return true;
}