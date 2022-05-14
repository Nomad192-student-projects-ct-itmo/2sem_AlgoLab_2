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
		size_t deep = 1;
		Node *p;
		Node *l = nullptr;
		Node *r = nullptr;

		Node(const T &x) noexcept : x(x), p(nullptr) {}
		Node(const T &x, Node *p) noexcept : x(x), p(p) {}
		~Node() noexcept
		{
			delete l;
			delete r;
		}
	};
	size_t n = 0;
	Node *root = nullptr;

public:
	~AVL() noexcept {delete root;} 

	bool insert 	(const T x) noexcept;
	bool del 		(const T x) noexcept;
	bool exists 	(const T x) 		const noexcept;
	bool next 		(const T x, T *res) const noexcept;
	bool prev 		(const T x, T *res) const noexcept;

	void full_print() const noexcept;
	void full_print_stream(std::ostream &out) const noexcept;

private:
	bool insert_rq(Node *cur, const T &x) noexcept;
	void del_node(Node *cur) noexcept;
	Node *search_rq(Node *cur, const T &x) const noexcept;
	bool next_rq(Node *cur, const T x, T *res) const noexcept;
	bool prev_rq(Node *cur, const T x, T *res) const noexcept;

	void full_print_rq(const Node *cur, size_t &ind) const noexcept;
	void full_print_stream_rq(const Node *cur, size_t &ind, std::ostream &out) const noexcept;
	
	void swap_val(Node *a, Node *b) noexcept;
	void swap_childs(Node *cur) noexcept;
	void restore_parent(Node *cur) noexcept;
	void balancing_node(Node *cur) noexcept;
	void small_left_rotation(Node *cur) noexcept;
	void large_left_rotation(Node *cur) noexcept;
	void small_right_rotation(Node *cur) noexcept;
	void large_right_rotation(Node *cur) noexcept;
	void balancing_tree(Node *cur) noexcept;
};

#endif