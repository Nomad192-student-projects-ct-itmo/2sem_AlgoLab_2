#include <cstdio>
#include <iostream>
#include <sstream>

#define MAX(x, y) ((x > y) ? (x) : (y))

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
			size_t deep = 1;
			Node *p;
			Node *l = nullptr;
			Node *r = nullptr;

			Node(T &x) : x(x), p(nullptr) {}
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
		//Node *serch(T x);
		Node *search_rq(Node *cur, T &x);
		//void del_leaf(Node *cur, Node *parent);
		//T del_right_rq(Node *cur);
		//T del_left_rq(Node *cur);
		void del_node(Node *cur);
		bool next_rq(Node *cur, T x, T *res);
		bool prev_rq(Node *cur, T x, T *res);
		//bool del_rq(Node *cur, T x);

		void full_print_rq(Node *cur, size_t &ind);
		void full_print_stream_rq(Node *cur, size_t &ind, std::ostream &out);
		bool insert_rq(Node *cur, T &x);
		void swap_val(Node *a, Node *b);
		void swap_childs(Node *cur);
		void restore_parent(Node *cur);
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
	if 		(x < cur->x) {if (!cur->l) {return cur;} else next = cur->l;}
	else if (x > cur->x) {if (!cur->r) {return cur;} else next = cur->r;}

	return search_rq(next, x);
}

bool AVL::exists(T x)
{
	//printf("ex %" TREE_TYPE_SP "\n", x);
	if(!root) return false;
	Node *cur = search_rq(root, x);
	if(cur->x == x) return true;
	return false;
}

bool AVL::next(T x, T *res)
{
	//printf("ex %" TREE_TYPE_SP "\n", x);
	if(!root) return false;

	return next_rq(root, x, res);
	// Node *cur = search_rq(root, x);
	// if(cur->x == x) 
	// {
	// 	if(!cur->r) return false;
	// 	cur = search_rq(cur, x);
	// 	*res = cur->x;
	// 	return true;
	// }
	// if(cur->x < x) if return false;
	// *res = cur->x;
	// return true;
}

bool AVL::prev(T x, T *res)
{
	//printf("ex %" TREE_TYPE_SP "\n", x);
	if(!root) return false;

	return prev_rq(root, x, res);
	// Node *cur = search_rq(root, x);
	// if(cur->x == x) 
	// {
	// 	if(!cur->r) return false;
	// 	cur = search_rq(cur, x);
	// 	*res = cur->x;
	// 	return true;
	// }
	// if(cur->x < x) if return false;
	// *res = cur->x;
	// return true;
}


bool AVL::next_rq(Node *cur, T x, T *res)
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
	Node *next;
	if 		(x < cur->x) {*res = cur->x; if (!cur->l) {return true; } else {next_rq(cur->l, x, res); return true;} }
	else if (x > cur->x) {if (!cur->r) {return false; } else next = cur->r;}

	return next_rq(next, x, res);
}

bool AVL::prev_rq(Node *cur, T x, T *res)
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
	Node *next;
	if 		(x < cur->x) {if (!cur->l) {return false; } else next = cur->l;}
	else if (x > cur->x) {*res = cur->x; if (!cur->r) {return true; } else {prev_rq(cur->r, x, res); return true;} }

	return prev_rq(next, x, res);
}

bool AVL::insert(T x)
{
	//printf("insert\n");
	if(root == nullptr)
	{
		root = new Node{x};
        n++;
       // printf("end inset root\n");
		return true;
	}
	bool result = insert_rq(root, x);
	//printf("end insert\n");
	return result;
}

/*
void AVL::del_leaf(Node *cur, Node *parent)
{
	if(parent->r == cur) parent->r = nullptr;
	else 				 parent->l = nullptr;
	delete cur;
}

T AVl::serch_near_and_del_rq(Node *cur, T x)
{
	Node *next;
	if(x < cur->x)
	{
		if(!cur->l->l) 
		{
			T res = cur->l->x;
			Node *buf = cur->l;
			cur->l = cur->l->r;
			delete buf;
			return res;
		}
		next = cur->l;
	}
	else if (x > cur->x)
	{
		if(!cur->r->r) 
		{
			T res = cur->r->x;
			Node *buf = cur->r;
			cur->r = cur->r->l;
			delete buf;
			return res;
		}
		next = cur->r;
	}

	T res = serch_near_and_del_rq(next, x);
	balancing_node(cur);
    balancing_tree(cur);
    return res;
}*/
/*
AVL::T AVL::del_right_rq(Node *cur)
{
	if(!cur->l->l)
	{
		Node *buf = cur->l;
		cur->l = cur->l->r;
		T res = buf->x;
		delete buf;
		balancing_node(cur->l);
		return res;
	}
	T res = del_right_rq(cur->l);
	balancing_node(cur);
    balancing_tree(cur);
    return res;
}

AVL::T AVL::del_left_rq(Node *cur)
{
	if(!cur->r->r)
	{
		Node *buf = cur->r;
		cur->r = cur->r->l;
		T res = buf->x;
		delete buf;
		balancing_node(cur->r);
		return res;
	}
	T res = del_left_rq(cur->r);
	balancing_node(cur);
    balancing_tree(cur);
    return res;
}*/

void AVL::del_node(Node *cur)
{
	n--;
	//printf("l=%d r=%d %d\n", cur->l == nullptr, cur->r == nullptr, cur->l == nullptr && cur->r == nullptr);
	if(cur->l == nullptr && cur->r == nullptr)
	{
		//printf("del leaf %" TREE_TYPE_SP "\n", cur->x);
		//printf("par %" TREE_TYPE_SP "\n", cur->p->x);
		Node *p_cur = cur->p;

		if(p_cur->l == cur) p_cur->l = nullptr;
		else 				p_cur->r = nullptr;	
		delete cur;	

		while(p_cur)
		{
			balancing_node(p_cur);
			balancing_tree(p_cur);
			p_cur = p_cur->p;
		} 

		return;
	}

	Node *leaf;
	if(cur->r)
	{
		//printf("del right\n");
		leaf = search_rq(cur->r, cur->x);
		//printf("node search %" TREE_TYPE_SP "\n", leaf->x);
		Node *p_leaf = leaf->p;
		//printf("par leaf=%" TREE_TYPE_SP "\n", p_leaf->x);
		if(p_leaf->l == leaf) {
			//printf("r %d %" TREE_TYPE_SP" \n", leaf->r, leaf->r->x); 
			p_leaf->l = leaf->r; 
			}
		else { 
			//printf("l\n"); 
			p_leaf->r = leaf->r;}
		restore_parent(p_leaf);

		//printf("old val %" TREE_TYPE_SP "\n", cur->x);
		cur->x = leaf->x;
		//printf("new val %" TREE_TYPE_SP "\n", cur->x);
		leaf->r = nullptr;
		delete leaf;
		//printf("p_l=%d p_r=%d\n", p_leaf->l, p_leaf->r);
		//if(p_leaf->l) printf("p_l=%" TREE_TYPE_SP "\n", p_leaf->l->x);
		//if(p_leaf->r) printf("p_r=%" TREE_TYPE_SP "\n", p_leaf->r->x);
		while(p_leaf)
		{
			balancing_node(p_leaf);
			balancing_tree(p_leaf);
			p_leaf = p_leaf->p;
		} 
		return;
	}

	//printf("del left\n");
	swap_val(cur, cur->l);
	delete cur->l;
	cur->l = nullptr;
	while(cur)
	{
		balancing_node(cur);
		balancing_tree(cur);
		cur = cur->p;
	} 

	// if(cur->b >= 0)
	// {
	// 	if(!cur->l->r)
	// 	{
	// 		cur->x = cur->l->x;
	// 		cur->l = cur->l->l;
	// 		balancing_node(cur);
	// 		return;
	// 	}
	// 	else if(!cur->l->r->r)
	// 	{
	// 		cur->x = cur->l->r->x;
	// 		cur->l->r = cur->l->r->l;
	// 		balancing_node(cur->l);
	// 		balancing_node(cur);
 //   			balancing_tree(cur);
 //   			return;
	// 	}
	// 	cur->x = del_left_rq(cur->l);
	// }
	// else
	// {
	// 	if(!cur->r->l)
	// 	{
	// 		cur->x = cur->r->x;
	// 		cur->r = cur->r->r;
	// 		balancing_node(cur);
	// 		return;
	// 	}
	// 	else if(!cur->r->l->l)
	// 	{
	// 		cur->x = cur->r->l->x;
	// 		cur->r->l = cur->r->l->r;
	// 		balancing_node(cur->r);
	// 		balancing_node(cur);
 //   			balancing_tree(cur);
 //   			return;
	// 	}
	// 	cur->x = del_right_rq(cur->r);
	// }

	// balancing_node(cur);
 //    balancing_tree(cur);

	// T x = cur->x;
	// Node *near = cur->r;
	// Node *near_parent = cur;
	// if(!near)
	// {
	// 	near = cur->l;
	// }
	// else if(near->l)
	// {
	// 	while(near->l->l) near = near->l;
	// 	near_parent = near;
	// 	near = near->l;
	// }

	// swap_val(cur, near);
	// del_leaf(near, near_parent);

	// Node *near;
	// if (l_near && r_near)
	// 	near = ((x - l_near->x) < (r_near->x - x) ? l_near : r_near);
	// else if (l_near) near = l_near;
	// else if (r_near) near = r_near;
	// else return false;

	// swap_val(cur, near)
}

bool AVL::del(T x)
{
	//printf("del\n");
	if(!root) {
		//printf("del end root == nulltpr\n"); 
		return false;}

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
	Node *cur = search_rq(root, x);
	//printf("search %" TREE_TYPE_SP "\n", cur->x);
	if(cur->x != x)
		return false;
	del_node(cur);
	return true;

/*	if(!root) return false;
	Node *parent = nullptr;
	Node *cur = search_rq(root, X, parent);
	if(cur->x != x) return false;
	if(!cur->l && !cur->r) 
	{
		if(parent)
		{
			if(parent->l->x == x)
				parent->l = nullptr
			else parent->r = nullptr
		}
		else root = nullptr;
		delete cur;
	}
	if()*/

}
/*
bool AVL::del_rq(Node *cur, T x)
{
	Node *next;
	if(x < cur->x)
	{
        if(cur->l == nullptr) return false;
        if(cur->l->x == x)
        {
        	n--;
        	if(!cur->l->l && !cur->l->r)
        	{
        		delete cur->l;
        		cur->l = nullptr;
        	}
        	else
        	{
        		del_node(cur->l);
        	}
    		balancing_node(cur);
			balancing_tree(cur);        	
        	return true;
        }
        next = cur->l;
	}
	else if(x > cur->x)
	{
        if(cur->r == nullptr) return false;
        if(cur->r->x == x)
        {
        	n--;
        	if(!cur->r->l && !cur->r->r)
        	{
        		delete cur->r;
        		cur->r = nullptr;
        	}
        	else
        	{
        		del_node(cur->r);
        	}
    		balancing_node(cur);
			balancing_tree(cur);
        	return true;
        }
        next = cur->r;
	} 
	else return false; ///x == cur->x  

    if(del_rq(next, x))
    {
    	balancing_node(cur);
    	balancing_tree(cur);
    	return true;
    }
    return false;  ///x there is in the tree	
}*/

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
	//printf("bal %" TREE_TYPE_SP "\n", cur->x);
	size_t deep_l = 0, deep_r = 0;
	if(cur->l) deep_l = cur->l->deep;
	if(cur->r) deep_r = cur->r->deep;	

	cur->deep = MAX(deep_l, deep_r) + 1;
	cur->b = deep_l - deep_r;
	///printf("end bal, l=%zu r=%zu  d=%zu b=%hhd\n", deep_l, deep_r, cur->deep, cur->b);
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
	
	/*size_t cache[2];
	cache[0] = 0;
	cache[1] = 1;

	for (size_t i = 2; i <= 10; i++) {
	    cache[i%2] = cache[0] + cache[1] + 1;
	    printf("deep = %zu, n=%zu\n", i, cache[i%2]);
	}*/
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
				//printf("insert\n");
                unsigned int x;
                scanf("%u", &x);
                tree.insert(x);
				break;
			}
			case delete_hash:
			{
				//printf("delete\n");
                unsigned int x;
                scanf("%u", &x);
                tree.del(x);
				break;
			}
			case exists_hash:
			{
				//printf("exists\n");
                unsigned int x;
                scanf("%u", &x);
                printf("%s\n", tree.exists(x) ? "true" : "false");
				break;
			}
			case next_hash:
			{
				//printf("next\n")'
                unsigned int x;
                scanf("%u", &x);
                unsigned int res;
                printf((tree.next(x, &res) ? "%u\n" : "none\n"), res);
				break;
			}
			case prev_hash:
			{
				//printf("prev\n")'
                unsigned int x;
                scanf("%u", &x);
                unsigned int res;
                printf((tree.prev(x, &res) ? "%u\n" : "none\n"), res);
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