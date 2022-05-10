#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>

//#define TEST
#ifdef TEST
	#include "C_Test.h"
#else
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

		void insert(T x);

		void exists(T x);
		void full_print();
		void full_print_stream(std::ostream &out);

	private:
		//Node *serch(T x);
		Node *search_rq(Node *cur, T &x);
		void full_print_rq(Node *cur, size_t &ind);
		void full_print_stream_rq(Node *cur, size_t &ind, std::ostream &out);
		bool insert_rq(Node *cur, T &x);
		void swap_val(Node *a, Node *b);
		void swap_childs(Node *cur);
		void balancing_node(Node *cur);
		void small_left_rotation(Node *cur);
		void large_left_rotation(Node *cur);
		void small_right_rotation(Node *cur);
		void large_right_rotation(Node *cur);
		void balancing_tree(Node *cur);
	};
#endif

AVL::Node *AVL::search_rq(Node *cur, T &x)
{
	if (x == cur->x) {return cur;}
	Node *next;
	if (x < cur->x) {if (!cur->l) {return cur;} else next = cur->l;}
	if (x > cur->x) {if (!cur->r) {return cur;} else next = cur->r;}

	return search_rq(next, x);
}

void AVL::insert(T x)
{
	if(root == nullptr)
	{
		root = new Node{x};
        n++;
		return;
	}
	insert_rq(root, x);
}
void AVL::full_print()
{
	printf("n = %zu\n", n);
    size_t ind = 0;
    full_print_rq(root, ind);
	printf("%d\n", n);
}
void AVL::full_print_stream(std::ostream &out)
{
	out << n << '\n';
    size_t ind = 0;
    full_print_stream_rq(root, ind, out);
	out << n;
}

void AVL::full_print_rq(Node *cur, size_t &ind)
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

void AVL::full_print_stream_rq(Node *cur, size_t &ind, std::ostream &out)
{
	if(cur == nullptr) return;
	full_print_stream_rq(cur->l, ind, out);
	size_t ind_left = ind;
	full_print_stream_rq(cur->r, ind, out);
	size_t ind_right = ind;
    
    ind++;

    out << cur->x;
    out << ' ' << (cur->l ? (int)ind_left 	: -1);
    out << ' ' << (cur->r ? (int)ind_right	: -1);
    out << '\n';
}
void AVL::swap_val(Node *a, Node *b)
{
	T buf = a->x;
	a->x = b->x;
	b->x = buf;
}

void AVL::swap_childs(Node *cur)
{
	Node *buf = cur->r;
	cur->r = cur->l;
	cur->l = buf;
}

void AVL::balancing_node(Node* cur)
{
	cur->b = 0;
  	if(cur->l) cur->b += (1 + abs(cur->l->b));
    if(cur->r) cur->b -= (1 + abs(cur->r->b));
}

void AVL::small_left_rotation(Node *cur)
{
	Node *x = cur;
	Node *y = x->r;

	swap_val(x, y);
	swap_childs(x);
	swap_childs(y);

	Node *buf = x->r;
	x->r = y->l;
	y->l = buf;

	x->b = 0;
	y->b = 0;
}
void AVL::large_left_rotation(Node *cur)
{
	Node *x = cur;
	Node *y = x->r;
	Node *z = y->l;

	swap_val(x, z);
	y->l = z->r;
	z->r = x->l;
	x->l = z;
	swap_childs(z);

	z->b = 0;
	balancing_node(x);
	balancing_node(y);
}
void AVL::small_right_rotation(Node *cur)
{
	Node *x = cur;
	Node *y = x->l;

	swap_val(x, y);
	swap_childs(x);
	swap_childs(y);

	Node *buf = x->l;
	x->l = y->r;
	y->r = buf;

	x->b = 0;
	y->b = 0;
}

void AVL::large_right_rotation(Node *cur)
{	
	Node *x = cur;
	Node *y = x->l;
	Node *z = y->r;

	swap_val(x, z);
	y->r = z->l;
	z->l = x->r;
	x->r = z;
	swap_childs(z);

	z->b = 0;
	balancing_node(x);
	balancing_node(y);
}
void AVL::balancing_tree(Node *cur_root)
{
	if 		(cur_root->b == -2)
	{
		if 			(cur_root->r->b == -1)	small_left_rotation(cur_root);
		else if 	(cur_root->r->b == 1)	large_left_rotation(cur_root);
	}
	else if (cur_root->b == 2)
	{
		if 			(cur_root->l->b == 1)	small_right_rotation(cur_root);
		else if 	(cur_root->l->b == -1)	large_right_rotation(cur_root);
	}
}

bool AVL::insert_rq(Node *cur, T &x)
{
	Node *next;
	if(x < cur->x)
	{
        if(cur->l == nullptr)
        {
            cur->l = new Node{x};
            cur->b++;
            n++;
			return true;
        }
        next = cur->l;
	}
	else if(x > cur->x)
	{
        if(cur->r == nullptr)
        {
            cur->r = new Node{x};
            cur->b--;
            n++;
            return true;
        }
        next = cur->r;
	} else return false;  ///x == cur->x

    if(insert_rq(next, x))
    {
    	balancing_node(cur);
    	balancing_tree(cur);
    	return true;
    }
    return false;  ///x there is in the tree
}

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
		tree.full_print();	
	}
	return 32;
}


/* 
 * quick start
cd 2sem_AlgoLab_2\C\build
..\..\run_cmake\run

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