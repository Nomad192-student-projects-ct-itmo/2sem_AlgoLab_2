#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

#define MIN(x, y) ((x < y) ? (x) : (y))

#define TREE_TYPE unsigned int
#define TREE_TYPE_SP "u"

#define TEST
#ifdef TEST
	#include <cstdlib>
	#define TEST_LEN_OP (10)	//10
	#define N_TEST (1000000)	//1000000
	#define N_TEST_POINT MIN((10), TEST_LEN_OP)
	#define RANGE_VAL (100)	//1000000000
	#define OFFSET_VAL (1)
#endif

class AVL
{
private:
	typedef TREE_TYPE T;
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
		printf("%d\n", n);
	}
	void full_print_stream(std::ostream &out)
	{
		out << n << '\n';
        size_t ind = 0;
        full_print_stream_rq(root, ind, out);
		out << 1;
	}

private:
	void full_print_rq(Node *cur, size_t &ind)
	{
		if(cur == nullptr) return;
		full_print_rq(cur->l, ind);
		size_t ind_left = ind;
		full_print_rq(cur->r, ind);
		size_t ind_right = ind;
        
        ind++;

        printf("%-2zu - %2" TREE_TYPE_SP " %2hhd -", ind, cur->x, cur->b);

        if(cur->l)
            printf(" (%zu)", ind_left);
        else
            printf(" (-1)");

        if(cur->r)
            printf(" (%zu)", ind_right);
        else
            printf(" (-1)");
        printf("\n");

	}
	void full_print_stream_rq(Node *cur, size_t &ind, std::ostream &out)
	{
		if(cur == nullptr) return;
		full_print_stream_rq(cur->l, ind, out);
		size_t ind_left = ind;
		full_print_stream_rq(cur->r, ind, out);
		size_t ind_right = ind;
        
        ind++;

        out << cur->x;
        out <<' ';
        if(cur->l)
            out << ind_left;
        else
            out << -1;
        out << ' ';
        if(cur->r)
            out << ind_right;
        else
        	out << -1;
        out << '\n';
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
		if(root.b == 2)
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
		typedef TREE_TYPE T;
		struct Node
		{
			T x;
			Node *next = nullptr;

			Node(T x) : x(x) {}
		};
		size_t n = 0;
		Node *first = nullptr;

		~AlmostTree()
		{
			Node *cur = first;
			while(cur)
			{
				Node *next = cur->next;
				delete cur;
				cur = next;
			}
		}

		void insert(T x)
		{
			Node *cur = first;
			while(cur)
			{
				if(cur->x == x) {return;}
				if(cur->next != nullptr)
				{
					cur->next = new Node(x);
					n++;
					return;
				}
			}
			first->next = new Node(x);
			n++;
		}
		void del(T x)
		{
			Node *cur = first;
			while(cur)
			{
				if(cur->next && cur->next->x) {
					cur->next = cur->next->next;
					delete cur->next;
					n--;
					return;
				}
			}
			if(first->x == x)
			{
				delete first;
				n--;
				first = nullptr;
			}
		}
		bool exists(T x)
		{
			Node *cur = first;
			while(cur)
			{
				if(cur->x == x)
					return true;
				cur = cur->next;
			}
			return false;
		}
		bool next(T x, T *next)
		{
			Node *cur = first;
			T min = x;
			while(cur)
			{
				if (cur->x > x)
				{
					min = cur->x;
					cur = cur->next;
					break;
				}
				cur = cur->next;
			}
			if(min == x) {return false;}
			while(cur)
			{
				if (cur->x > x && cur->x < min)
					min = cur->x;
				cur = cur->next;
			}
			if(min == x) {return false;}
			*next = min;
			return true;
		}
		bool prev(T x, T *prev)
		{
			Node *cur = first;
			T max = x;
			while(cur)
			{
				if (cur->x < x)
				{
					max = cur->x;
					cur = cur->next;
					break;
				}
				cur = cur->next;
			}
			if(max == x) {return false;}
			while(cur)
			{
				if (cur->x < x && cur->x > max)
					max = cur->x;
				cur = cur->next;
			}
			if(max == x) {return false;}
			*prev = max;
			return true;
		}
	};

	class TestTree
	{
	private:
		#define IND_NEU_VAL (-2)
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
		size_t current_add = 0;
		Node *data;

	public:
		TestTree(size_t n) : n(n), data(new Node[n]) {}
		~TestTree() {delete[] data;}

		void add(Node v)
		{
			if (current_add >= n) return;

			data[current_add++] = v;
			//printf("test tree add = %u %d %d\n", v.x, v.l, v.r);
		}

		bool isTree(size_t root)
		{
			//printf("isTree = %zu\n", root);
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
			//printf("check_rq_1 %d %d %d\n", el, data[el].l, data[el].r);
			if(el == IND_NEU_VAL) return true;

			if(data[el].l != IND_NEU_VAL && data[data[el].l].x >= data[el].x)
				return false;

			if(data[el].r != IND_NEU_VAL && data[data[el].r].x <= data[el].x)
				return false;
			
			return check_rq(data[el].l) && check_rq(data[el].r);
		}
	};

	bool test(class AVL &tree)
	{
		//printf("test_1\n");
		std::stringstream tree_output;
		tree.full_print_stream(tree_output);
		//std::cout << "tree output = \"" << tree_output.str() << "\"\n";

		size_t n;
		tree_output >> n;
		//printf("n = %zu\n", n);
		TestTree test_tree(n);

		//printf("test_2\n");
		for (size_t i = 0; i < n; i++)
		{
			TREE_TYPE x;
			size_t l, r;
			tree_output >> x >> l >> r;
			//printf("node = %u %d %d\n", x, l, r);
			if((l != -1 && r != -1) && l > r)
				return false; 
			test_tree.add(TestTree::Node{x, --l, --r});
		}
		//printf("test_3\n");
		size_t root;
		tree_output >> root;
		//printf("root = %zu\n", root);
		return test_tree.isTree(--root);
	}
	bool full_test()
	{
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

			Req(Type type, TREE_TYPE x) : type(type), x(x) {}
		};
		Req *req_arr[TEST_LEN_OP];

		for (size_t length = 1; length <= TEST_LEN_OP; length++)
	    {
	    	if((length-1) % (TEST_LEN_OP/N_TEST_POINT) == 0)
	    		printf("	len test %g%%\n", ((double)(length-1) / (double)TEST_LEN_OP) * 100);

	    	for(size_t n_attempt = 0; n_attempt < N_TEST; n_attempt++)
	        {
	        	AVL tree;
	        	//AlmostTree test;

	        	for(size_t i = 0; i < length; i++)
	        	{//Req::Type(rand() % 5)
	        		req_arr[i] = new Req(Req::Type(0), (rand() % RANGE_VAL) + OFFSET_VAL);
	        		switch(req_arr[i]->type)
	        		{
	        			case Req::Type::INSERT: {
	        				tree.insert(req_arr[i]->x); 
	        				//test.insert(req_arr[i].x); 
	        				break;
	        			}
	        			//case Req::Type::EXISTS: {}
	        		}
	        	}
	        	//printf("a\n");
	        	if(!test(tree))
		    	{
		    		printf("Error with data:\n");
		    		printf("%d\n", length);
		    		for (size_t i = 0; i < length; i++)
			    	{
			    		printf("%u %u\n", req_arr[i]->type, req_arr[i]->x);
			    		delete req_arr[i];
			    	}
			    	printf("\nAVL full print stream:\n");
			    	tree.full_print_stream(std::cout);
			    	printf("\nAVL full print:\n");
			    	tree.full_print();
			    	return false;
		    	}
		    	//printf("b\n");
	    		for (size_t i = 0; i < length; i++)
		    		delete req_arr[i];
		    	//printf("c\n");

				/*AVL avl(length);

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
		    		avl.insert(data[i]);
		    	}
		    	if(!test(avl, length))
		    	{
		    		printf("Error with data:\n");
		    		printf("%d\n", length);
		    		for (size_t i = 0; i < length; i++)
			    	{
			    		printf("%u ", data[i]);
			    	}
			    	printf("\nBST full print:\n");
			    	avl.full_print();
			    	return false;
		    	}*/
	    	}
	    }
	    printf("	len test 100%% - OK\n");
	    return true;
	}
#endif

/*static bool eq_str(const char a[], const char b[])
{
	for(size_t i = 0; a[i] == b[i]; i++)
		if(a[i]=='\0' && b[i]=='\0')
			return true;	
	return false;
}*/

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

	AVL tree;

	for(char op[7]; scanf("%6s", op) != EOF && n--;)
	{
		switch(hash_str(op))
		{
			case insert_hash:
			{
				printf("insert\n");
                unsigned int x;
                scanf("%u", &x);
                tree.insert(x);
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

	    //std::streambuf *buffer = std::cout.rdbuf();
        //std::cout.rdbuf(std::cin.rdbuf());
		

		tree.full_print();

        //std::cout.rdbuf(buffer);
		
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