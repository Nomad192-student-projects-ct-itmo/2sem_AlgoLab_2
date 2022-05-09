#include <cstdio>
#include <iostream>
#include <sstream>

#define TEST
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
		void full_print();
		void full_print_stream(std::ostream &out);

	private:
		void full_print_rq(Node *cur, size_t &ind);
		void full_print_stream_rq(Node *cur, size_t &ind, std::ostream &out);
		void insert_rq(Node *el, T &x);
	};
#endif

void AVL::insert(T x)
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
void AVL::full_print()
{
	printf("n = %zu\n", n);
    size_t ind = 0;
    full_print_rq(root,ind);
	printf("%d\n", n);
}
void AVL::full_print_stream(std::ostream &out)
{
	out << n << '\n';
    size_t ind = 0;
    full_print_stream_rq(root, ind, out);
	out << 1;
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
    out << ' ' << (cur->l ? ind_left 	: -1);
    out << ' ' << (cur->r ? ind_right	: -1);
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
void AVL::insert_rq(Node *el, T &x)
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
	#ifdef int 
	printf("f");
	#endif
	
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