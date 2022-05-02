#include <cstdio>

#define MIN(x, y) ((x < y) ? (x) : (y))

//#define TEST
#ifdef TEST
	#include <cstdlib>
	#define TEST_LEN_ARR (10)
	#define N_TEST (1000000)
	#define N_TEST_POINT MIN((10), TEST_LEN_ARR)
	#define RANGE_VAL (1000000000) 
	#define OFFSET_VAL (1)
#endif


#define AVL_TREE

#ifdef AVL_TREE
	class AVL
	{
	private:
		typedef unsigned int T;
		#define IND_NEU_VAL (size_t)(-2)
		//#define DATA_NEU_VAL (T)(0)
		#define DATA_SP "u"
		#define IND_SP "d"
		struct Node
		{
			T x;
			size_t l;
			size_t r;
			signed char b;
			//size_t h_l;
			//size_t h_r;
		};
		size_t n;
		struct Node *data;
		size_t current_add;
	public:
		AVL(size_t n) : n(n), data(new struct Node[n]), current_add(0) {}
		~AVL() {delete[] data;}

		void add(T x)
		{
			if(current_add == 0)
			{
				data[current_add++] = Node{x, IND_NEU_VAL, IND_NEU_VAL, 0};
				return;
			}
			add_rq(0, x);
			balancing();
		}
		void full_print()
		{
			printf("%zu\n", n);
			for(size_t i = 0; i < current_add; i++)
				printf("%" DATA_SP " %" IND_SP " %" IND_SP "\n", data[i].x, data[i].l+1, data[i].r+1);
			printf("%d", 0+1);
		}

	private:
		friend bool test(class AVL &bst, class AlmostTree &tree);
		void swap(size_t i, size_t j)
		{
			Node buf = data[i];
			data[i] = data[j];
			data[j] = buf;
		}
		void swap_val(size_t i, size_t j)
		{
			T x = data[i].x;
			data[i].x = data[j].x;
			data[j].x = x;
		}
		void swap_lr(size_t el)
		{
			size_t buf = data[el].r;
			data[el].r = data[el].l;
			data[el].l = buf;
		}
		void swap_childs(size_t el)
		{
			if(data[el].l != IND_NEU_VAL && data[el].r != IND_NEU_VAL)
				swap(data[el].r, data[el].l);
			swap_lr(el);
		}
		void check_rl(size_t el)
		{
			if(data[el].l == IND_NEU_VAL || data[el].r == IND_NEU_VAL)
				return;
			if(data[el].l > data[el]. r)
				swap_childs(el);
		}
		void small_left_rotation()
		{
			size_t x = 0;
			size_t y = data[0].r;
			swap(x, y);
			x = y;
			y = 0;
			data[x].r = data[y].l;
			check_rl(x);
			data[y].l = x;
			check_rl(y);
		}
		void large_left_rotation()
		{
			size_t x = 0;
			size_t y = data[0].r;
			size_t z = data[data[0].r].l;
			swap(x, z);
			x = z;
			z = 0;
			data[x].r = data[z].l;
			check_rl(x);
			data[z].l = x;
			data[y].l = data[z].r;
			check_rl(y);
			data[z].r = y;
			check_rl(z);
		}
		void small_right_rotation()
		{
			size_t x = 0;
			size_t y = data[0].l;
			swap(x, y);
			x = y;
			y = 0;
			data[x].l = data[y].r;
			check_rl(x);
			data[y].r = x;
			check_rl(y);
		}
		void large_right_rotation()
		{
			size_t x = 0;
			size_t y = data[0].l;
			size_t z = data[data[0].l].r;
			swap(x, z);
			x = z;
			z = 0;
			data[x].l = data[z].r;
			check_rl(x);
			data[z].r = x;
			data[y].r = data[z].l;
			check_rl(y);
			data[z].l = y;
			check_rl(z);
		}
		void balancing()
		{
			if(data[0].b == -2)
			{
				if(data[data[0].r].b == -1)
				{
					small_left_rotation();
					return;
				}

				if(data[data[0].r].b == 1)
				{
					large_left_rotation();
					return;
				}
			}
			if(data[0].b == 2)
			{
				if(data[data[0].l].b == 1)
				{
					small_right_rotation();
					return;
				}

				if(data[data[0].l].b == -1)
				{
					large_right_rotation();
					return;
				}
			}
		}
		void add_rq(size_t el, T &x)
		{
			if(x < data[el].x && data[el].l == IND_NEU_VAL)
			{
				data[current_add] = Node{x, IND_NEU_VAL, IND_NEU_VAL, 0};
				data[el].l = current_add++;
				check_rl(el);
				data[el].b++;
				return;
			}
			if(x > data[el].x && data[el].r == IND_NEU_VAL)
			{
				data[current_add] = Node{x, IND_NEU_VAL, IND_NEU_VAL, 0};
				data[el].r = current_add++;
				data[el].b--;
				return;
			}

			x < data[el].x ? data[el].b++ : data[el].b--;
			add_rq(x < data[el].x ? data[el].l : data[el].r, x);
		}
	};
#else
	class BST
	{
	private:
		typedef unsigned int T;
		#define IND_NEU_VAL (size_t)(-2)
		//#define DATA_NEU_VAL (T)(0)
		#define DATA_SP "u"
		#define IND_SP "d"
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
			if(current_add == 0)
			{
				data[current_add++] = Node{x, IND_NEU_VAL, IND_NEU_VAL};
				return;
			}
			add_rq(0, x);
		}
		void full_print()
		{
			printf("%zu\n", n);
			for(size_t i = 0; i < current_add; i++)
				printf("%" DATA_SP " %" IND_SP " %" IND_SP "\n", data[i].x, data[i].l+1, data[i].r+1);
			printf("%d", 0+1);
		}

	private:
		friend bool test(class BST &bst, class AlmostTree &tree);
		void add_rq(size_t el, T &x)
		{
			if(x < data[el].x && data[el].l == IND_NEU_VAL)
			{
				if(data[el].r != IND_NEU_VAL)
				{
					data[current_add] = data[data[el].r];
					data[data[el].r] = Node{x, IND_NEU_VAL, IND_NEU_VAL};
					data[el].l = data[el].r;
					data[el].r = current_add;
				}
				else
				{
					data[current_add] = Node{x, IND_NEU_VAL, IND_NEU_VAL};
					data[el].l = current_add;
				}
				
				current_add++;
				return;
			}
			add_rq(x < data[el].x ? data[el].l : data[el].r, x);
		}
	};
#endif


#ifdef TEST
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

#ifdef AVL_TREE
	bool test(class AVL &bst, class AlmostTree &tree)
#else
	bool test(class BST &bst, class AlmostTree &tree)
#endif
	{
		for (size_t i = 0; i < bst.current_add; i++)
		{
			if(bst.data[i].l > bst.data[i].r && (bst.data[i].l != -2 && bst.data[i].r != -2))
				return false; 
			tree.add({bst.data[i].x, bst.data[i].l, bst.data[i].r});
		}
		return tree.check(0);
	}
	bool full_test()
	{
		unsigned int data[TEST_LEN_ARR];
		for (size_t length = 1; length <= TEST_LEN_ARR; length++)
	    {
	    	if((length-1) % (TEST_LEN_ARR/N_TEST_POINT) == 0)
	    		printf("	len test %g%%\n", ((double)(length-1) / (double)TEST_LEN_ARR) * 100);

	    	for(size_t n_attempt = 0; n_attempt < N_TEST; n_attempt++)
	        {
#ifdef AVL_TREE
				AVL bst(length);
#else
				BST bst(length);
#endif

		    	AlmostTree tree(length);
		    	for (size_t i = 0; i < length; i++)
		    	{
		    		data[i] = (rand() % RANGE_VAL) + OFFSET_VAL;
		    		for (size_t y = 0; y < i; y++)
		    		{
		    			if(data[y] == data[i])
		    			{
		    				data[i] = (rand() % RANGE_VAL) + OFFSET_VAL;
		    				y = -1;
		    			}
		    		}
		    		bst.add(data[i]);
		    	}
		    	if(!test(bst, tree))
		    	{
		    		printf("Error with data:\n");
		    		printf("%d\n", length);
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
	    printf("	len test 100%% - OK\n");
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

#ifdef AVL_TREE
	AVL bst(n);
#else
	BST bst(n);
#endif


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
..\..\run_cmake\run

* move
cd 2sem_AlgoLab_2\B\build
cd B\build

* update run_cmake
git submodule update --remote
*/