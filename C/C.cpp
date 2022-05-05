#include <cstdio>

#define MIN(x, y) ((x < y) ? (x) : (y))

//#define TEST
#ifdef TEST
	#include <cstdlib>
	//#define TEST_LEN_ARR (10)
	//#define N_TEST (1000000)
	//#define N_TEST_POINT MIN((10), TEST_LEN_ARR)
	//#define RANGE_VAL (1000000000) 
	//#define OFFSET_VAL (1)
#endif


class AVL
{
private:
	typedef unsigned int T;
	#define DATA_SP "u"
	struct Node
	{
		T x;
		signed char b = 0;
		Node *l = nullptr;
		Node *r = nullptr;

		Node(T &x) : x(x) {}
		~Node()
		{
			delete l;
			delete r;
		}
	};
	size_t n = 0;
	Node *root = nullptr;
public:
	~AVL() {delete root;}

	void insert(T x)
	{
		if(root == nullptr)
		{
			root = new Node{x};
            n++;
			return;
		}
		insert_rq(root, x);
		//balancing();
	}
	void full_print()
	{

		printf("n = %zu\n", n);
        size_t ind = 0;
        full_print_rq(root,ind);
		printf("%d\n", 1);
	}

private:
	friend bool test(class AVL &, class AlmostTree &);
	void full_print_rq(Node *cur, size_t &ind)
	{
		if(cur == nullptr) return;

        ind++;
        printf("%-2zu - %2" DATA_SP " %2hhd -", ind, cur->x, cur->b);
        if(cur->l)
        {
            printf(" (%2d)", ind + 1);
        }
        else
            printf(" (-1)");
        if(cur->r)
            printf(" (%2d)", ind + 1 + (cur->l != nullptr));
        else
            printf(" (-1)");
        printf("\n");

        full_print_rq(cur->l, ind);
		full_print_rq(cur->r,ind);
	}
	/*static void swap(Node *a, Node *b)
	{
		Node buf = *a;
		*a = *b;
		*b = buf;
	}
    static void swap_val(Node *a, Node *b)
	{
		T x = a->x;
		a->x = b->x;
		b->x = x;
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
		if(root->b == -2)
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
	}*/
	void insert_rq(Node *el, T &x)
	{
        Node *next;
		if(x < el->x)
		{
            el->b++;
            if(el->l == nullptr)
            {
                el->l = new Node{x};
                n++;
                return;
            }
            next = el->l;
		}
		else if(x > el->x)
		{
            el->b--;
            if(el->r == nullptr)
            {
                el->r = new Node{x};
                n++;
                return;
            }
            next = el->r;
		} else return;  ///x == el.x

        insert_rq(next, x);
	}
};

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

static bool eq_str(const char a[], const char b[])
{
	for(size_t i = 0; a[i] == b[i]; i++)
		if(a[i]=='\0' && b[i]=='\0')
			return true;	
	return false;
}

typedef unsigned long int hash_type;

static constexpr hash_type hash_str(const char str[])
{
    hash_type result=0;
	for(size_t i=0, m=1; str[i]!='\0'; i++, m*=131)
		result += (str[i]*m);
	return result;
}

constexpr hash_type insert_hash =  hash_str("insert");
constexpr hash_type delete_hash =  hash_str("delete");
constexpr hash_type exists_hash =  hash_str("exists");
constexpr hash_type next_hash   =  hash_str("next");
constexpr hash_type prev_hash   =  hash_str("prev");

int main()
{

#ifdef TEST
	return !full_test();
#endif

    size_t n = 100;

	AVL avl;

	for(char op[7]; scanf("%6s", op) != EOF && n--;)
	{
		switch(hash_str(op))
		{
			case insert_hash:
			{
				printf("insert\n");
                unsigned int x;
                scanf("%u", &x);
                avl.insert(x);
				break;
			}
			case delete_hash:
			{
				printf("2\n");
				break;
			}
			case exists_hash:
			{
				printf("3\n");
				break;
			}
			case next_hash:
			{
				printf("4\n");
				break;
			}
			case prev_hash:
			{
				printf("5\n");
				break;
			}
			default:
			{
                if(op[0] == '^' && op[1] == 'Z')
                    return 0;
				printf("Error: unknown command - \"%s\"!\n", op);
				return -1;
			}
		}
		// unsigned int x;
		// scanf("%u", &x);
		// avl.add(x);
		avl.full_print();
	}
	return 0;
}


/* 
 * set 
mkdir build & cd build & cmake -G "MinGW Makefiles" ..

* build and run
cmake --build . && (echo START & C)
echo return code: %errorlevel%

* or
..\..\run_cmake\run

* move
cd 2sem_AlgoLab_2\C\build
cd 2sem_AlgoLab_2\C
cd C\build

* update run_cmake
git submodule update --remote
*/