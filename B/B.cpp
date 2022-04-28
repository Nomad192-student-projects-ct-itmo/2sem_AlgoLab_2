#include <cstdio>


#define TEST

#ifdef TEST
#include <cstdlib>
#define TEST_LEN_ARR (10)
#define TEST_N (1000000)
class AlmostTree
{
private:
	typedef unsigned int T;
public:
	struct Node
	{
		T x;
		size_t l;
		size_t r;
	};
private:
	size_t n;
	size_t current_add;
	Node *data;

public:
	AlmostTree(size_t n) : n(n), data(new Node[n]), current_add(0) {}
	~AlmostTree() {delete[] data;}

	void add(Node v)
	{
		if (current_add >= n) return;

		data[current_add++] = v;
	}

	bool check(size_t root)
	{
		return check_rq(root);
	}
	void print()
	{
		printf("Tree(");
		for(size_t i = 0; i < n - 1; i++)
			printf("%u, ", data[i].x);
		printf("%u)\n", data[n-1].x);
	}
private:
	bool check_rq(size_t el)
	{
		if(el == -2) return true;

		if(data[el].l != -2 && data[data[el].l].x >= data[el].x)
			return false;

		if(data[el].r != -2 && data[data[el].r].x <= data[el].x)
			return false;

		return check_rq(data[el].l) && check_rq(data[el].r);
	}
};
#endif


class BST
{
private:
	typedef unsigned int T;
	struct Node
	{
		T x;
		size_t l;
		size_t r;
	};
	size_t n;
	struct Node *data;
	size_t current_add;
public:
	BST(size_t n) : n(n), data(new struct Node[n]), current_add(0) {}
	~BST() {delete[] data;}

	void add(T x)
	{
		//printf("add\n");
		if(current_add == 0)
		{
			data[current_add++] = Node{x, (size_t)-2, (size_t)-2};
			return;
		}
		//printf("add_rq\n");
		add_rq(x < data[0].x ? data[0].l : data[0].r, x, 0);
	}
	void full_print()
	{
		printf("%zu\n", n);
		for(size_t i = 0; i < current_add; i++)
			printf("%u %d %d\n", data[i].x, data[i].l+1, data[i].r+1);
		printf("%d", 0+1);
	}

private:
	friend bool test(class BST &bst, class AlmostTree &tree);
	void full_print_rq(size_t el)
	{
		if(el == (size_t)-2) return;
		printf("%u %d %d\n", data[el].x, data[el].l+1, data[el].r+1);
		full_print_rq(data[el].l);
		full_print_rq(data[el].r);
	}
	void add_rq(size_t el, T &x, size_t prev)
	{

		if(el == (size_t)-2)
		{
			data[current_add] = Node{x, (size_t)-2, (size_t)-2};
			x < data[prev].x ? (data[prev].l = current_add) : (data[prev].r = current_add);
			current_add++;
			return;
		}

		add_rq(x < data[el].x ? data[el].l : data[el].r, x, el);
	}
};

#ifdef TEST
bool test(class BST &bst, class AlmostTree &tree)
{
	for (size_t i = 0; i < bst.current_add; i++)
		tree.add({bst.data[i].x, bst.data[i].l, bst.data[i].r});
	if(!tree.check(0))
		return false;
	return true;
}
bool full_test()
{
	unsigned int data[TEST_LEN_ARR];
	for (size_t length = 1; length < TEST_LEN_ARR; length++)
    {
    	printf("    test len %d\n", length);
    	for(size_t n_attempt = 0; n_attempt < TEST_N; n_attempt++)
        {
	    	BST bst(length);
	    	AlmostTree tree(length);
	    	for (size_t i = 0; i < length; i++)
	    	{
	    		data[i] = (rand() % 20) + 1;
	    		for (size_t y = 0; y < i; y++)
	    		{
	    			if(data[y] == data[i])
	    			{
	    				data[i] = (rand() % 20) + 1;
	    				y = -1;
	    			}
	    		}
	    		bst.add(data[i]);
	    	}
	    	if(!test(bst, tree))
	    	{
	    		printf("Error with data: ");
	    		for (size_t i = 0; i < length; i++)
		    	{
		    		printf("%u ", data[i]);
		    	}
		    	printf("\nBST full print:\n");
		    	bst.full_print();
		    	return false;
	    	}
    	}
    }
    return true;
}
#endif

int main()
{
#ifdef TEST
	return !full_test();
#endif

    size_t n;
	scanf("%zu\n", &n);

	BST bst(n);

	while(n--)
	{
		unsigned int x;
		scanf("%u", &x);
		bst.add(x);
	}

	bst.full_print();
	return 0;
}


/* 
 * set 
mkdir build & cd build & cmake -G "MinGW Makefiles" ..

* build and run
cmake --build . && (echo START & B)
echo return code: %errorlevel%

* or
..\..\run B

* move
cd 2sem_AlgoLab_2\B\build
*/