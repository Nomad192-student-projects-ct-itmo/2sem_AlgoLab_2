#ifndef AVL_H
#define AVL_H

#include <cstdio>
class AVL
{
private:
	typedef TREE_TYPE T;
	struct Node
	{
		T x;
		size_t deep = 1;
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

	bool insert(T x);

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