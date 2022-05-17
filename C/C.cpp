#include <cstdio>
#include <iostream>

#define MAX(x, y) ((x > y) ? (x) : (y))

#define TREE_TYPE int
#define TREE_TYPE_SP "d"

//#define TEST
#ifdef TEST
	#include "C_Test.hpp"
#else
	class AVL
	{
	private:
		typedef TREE_TYPE T;
		struct Node
		{
			T x;
			signed char b = 0;
			size_t deep = 1;
			Node *p;
			Node *l = nullptr;
			Node *r = nullptr;

			explicit Node(T &x) : x(x), p(nullptr) {}
			Node(T &x, Node *p) : x(x), p(p) {}
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

		bool insert(T x);
		bool del(T x);
		bool exists(T x);
		bool next(T x, T *res);
		bool prev(T x, T *res);

		void full_print();
		void full_print_stream(std::ostream &out);

	private:
		static Node *search(Node *cur, T &x);
		void del_node(Node *cur);
		bool next_below(Node *cur, T x, T *res);
		bool prev_below(Node *cur, T x, T *res);

        void fix_balance_top(Node *cur);
		void full_print_rq(Node *cur, size_t &ind);
		void full_print_stream_rq(Node *cur, size_t &ind, std::ostream &out);
		bool insert_rq(Node *cur, T &x);
		static void swap_val(Node *a, Node *b);
		static void swap_childs(Node *cur);
		static void restore_parent(Node *cur);
		static void balancing_node(Node *cur);
		static void small_left_rotation(Node *cur);
		static void large_left_rotation(Node *cur);
		static void small_right_rotation(Node *cur);
		static void large_right_rotation(Node *cur);
		static void balancing_tree(Node *cur);
	};
#endif

AVL::Node *AVL::search(Node *cur, T &x)
{
    while (true)
    {
        if(x == cur->x) return cur;
        else if (x < cur->x) {if (!cur->l) {return cur;} else cur = cur->l;}
        else if (x > cur->x) {if (!cur->r) {return cur;} else cur = cur->r;}
    }
}

bool AVL::exists(T x)
{
	if(!root) return false;
	Node *cur = search(root, x);
	if(cur->x == x) return true;
	return false;
}

bool AVL::next(T x, T *res)
{
	if(!root) return false;

	return next_below(root, x, res);
}
bool AVL::next_below(Node *cur, T x, T *res)
{
    while(true)
    {
        if (x == cur->x)
        {
            if(!cur->r) return false;
            cur = cur->r;
            if(!cur->l) {*res = cur->x; return true;}
            while(cur->l) cur = cur->l;
            *res = cur->x;
            return true;
        }
        else if (x < cur->x) {
            *res = cur->x;
            if (!cur->l) {return true;}
            else {next_below(cur->l, x, res); return true;}
        }
        else if (x > cur->x) {if (!cur->r) {return false;} else cur = cur->r;}
    }
}


bool AVL::prev(T x, T *res)
{
	if(!root) return false;

	return prev_below(root, x, res);
}
bool AVL::prev_below(Node *cur, T x, T *res)
{
    while(true)
    {
        if (x == cur->x)
        {
            if(!cur->l) return false;
            cur = cur->l;
            if(!cur->r) {*res = cur->x; return true;}
            while(cur->r) cur = cur->r;
            *res = cur->x;
            return true;
        }
        else if	(x < cur->x) {if (!cur->l) {return false;} else cur = cur->l;}
        else if (x > cur->x) {
            *res = cur->x;
            if (!cur->r) {return true;}
            else {prev_below(cur->r, x, res); return true;}
        }
    }
}


bool AVL::insert(T x)
{
	if(root == nullptr)
	{
		root = new Node{x};
        n++;
		return true;
	}
	bool result = insert_rq(root, x);
	return result;
}
bool AVL::insert_rq(Node *cur, T &x)
{
	Node *next;
	if(x < cur->x)
	{
        if(cur->l == nullptr)
        {
            cur->l = new Node{x, cur};
			balancing_node(cur);          
            n++;
			return true;
        }
        next = cur->l;
	}
	else if(x > cur->x)
	{
        if(cur->r == nullptr)
        {
            cur->r = new Node{x, cur};
            balancing_node(cur);
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

void AVL::fix_balance_top(Node *cur)
{
    while(cur)
    {
        balancing_node(cur);
        balancing_tree(cur);
        cur = cur->p;
    }
}

bool AVL::del(T x)
{
    if(!root) return false;

    if(root->x == x)
    {
        if(!root->l && !root->r)
        {
            n--;
            delete root;
            root = nullptr;
            return true;
        }
        del_node(root);
        return true;
    }

    Node *cur = search(root, x);
    if(cur->x != x)
        return false;
    del_node(cur);
    return true;
}
void AVL::del_node(Node *cur)
{
	n--;
	if(!cur->l && !cur->r)
	{
		Node *p_cur = cur->p;

		if(p_cur->l == cur) p_cur->l = nullptr;
		else 				p_cur->r = nullptr;

		delete cur;

        fix_balance_top(p_cur);
	}
	else if(cur->r)
	{
		Node *leaf;
		leaf = search(cur->r, cur->x);
		Node *p_leaf = leaf->p;

		if(p_leaf->l == leaf)	p_leaf->l = leaf->r; 
		else  					p_leaf->r = leaf->r;

		restore_parent(p_leaf);

		cur->x = leaf->x;
		leaf->r = nullptr;
		delete leaf;

        fix_balance_top(p_leaf);
	}
	else
	{
		swap_val(cur, cur->l);
		delete cur->l;
		cur->l = nullptr;

        fix_balance_top(cur);
	}
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

    printf("%-2zu - x=%-2" TREE_TYPE_SP " h=%-2zu b=%-2hhd -", ind, cur->x, cur->deep, cur->b);

    if(cur->p)
    	printf(" p=%-2" TREE_TYPE_SP "", cur->p->x);
    else
    	printf(" pnot");

    if(cur->l)
        printf(" (%2zu)", ind_left);
    else
        printf(" (-1)");

    if(cur->r)
        printf(" (%2zu)", ind_right);
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

void AVL::restore_parent(Node *cur)
{
	if(cur->r) cur->r->p = cur;
	if(cur->l) cur->l->p = cur;
}

void AVL::balancing_node(Node* cur)
{
	size_t deep_l = 0, deep_r = 0;
	if(cur->l) deep_l = cur->l->deep;
	if(cur->r) deep_r = cur->r->deep;	

	cur->deep = MAX(deep_l, deep_r) + 1;
	cur->b = (signed char)(deep_l - deep_r);
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

	restore_parent(y);
	restore_parent(x);

	balancing_node(y);
	balancing_node(x);
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

	restore_parent(z);
	restore_parent(y);	
	restore_parent(x);

	balancing_node(z);
	balancing_node(y);
	balancing_node(x);
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

	restore_parent(y);
	restore_parent(x);

	balancing_node(y);
	balancing_node(x);
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

	restore_parent(z);
	restore_parent(y);	
	restore_parent(x);

	balancing_node(z);
	balancing_node(y);
	balancing_node(x);
}
void AVL::balancing_tree(Node *cur_root)
{
	if (cur_root->b == -2)
	{
		if 		(cur_root->r->b == -1 || cur_root->r->b == 0)	small_left_rotation(cur_root);
		else if (cur_root->r->b == 1)							large_left_rotation(cur_root);
		else {printf("Error balance AVL, b = -2, b right = %d\n", cur_root->r->b);}
	}
	else if (cur_root->b == 2)
	{
		if 		(cur_root->l->b == 1 || cur_root->l->b == 0)	small_right_rotation(cur_root);
		else if (cur_root->l->b == -1)							large_right_rotation(cur_root);
		else {printf("Error balance AVL, b = 2, b left = %d\n", cur_root->l->b);}
	}
	else if (cur_root->b > 2 || cur_root->b < -2) {printf("Error balance, b = %d\n", cur_root->b);}
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

	AVL tree;

	for(char op[7]; scanf("%6s", op) != EOF;)
	{
		switch(hash_str(op))
		{
			case insert_hash:
			{
				//printf("insert\n");
                TREE_TYPE x;
                scanf("%" TREE_TYPE_SP, &x);
                tree.insert(x);
				break;
			}
			case delete_hash:
			{
				//printf("delete\n");
                TREE_TYPE x;
                scanf("%" TREE_TYPE_SP, &x);
                tree.del(x);
				break;
			}
			case exists_hash:
			{
				//printf("exists\n");
                TREE_TYPE x;
                scanf("%" TREE_TYPE_SP, &x);
                printf("%s\n", tree.exists(x) ? "true" : "false");
				break;
			}
			case next_hash:
			{
				//printf("next\n")'
                TREE_TYPE x;
                scanf("%" TREE_TYPE_SP, &x);
                TREE_TYPE res;
                if(tree.next(x, &res))
                	printf("%" TREE_TYPE_SP "\n", res);
                else
                	printf("none\n");
				break;
			}
			case prev_hash:
			{
				//printf("prev\n")'
                TREE_TYPE x;
                scanf("%" TREE_TYPE_SP, &x);
                TREE_TYPE res;
                if(tree.prev(x, &res))
                	printf("%" TREE_TYPE_SP "\n", res);
                else
                	printf("none\n");
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
		//tree.full_print();	
	}
	return 0;
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