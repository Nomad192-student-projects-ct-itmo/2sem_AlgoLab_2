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