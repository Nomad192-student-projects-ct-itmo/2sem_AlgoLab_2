#ifndef ALMOSTTREE_H
#define	ALMOSTTREE_H

#include <cstdio>
#include <iostream>

class AlmostTree ///List
{
private:
	typedef TREE_TYPE T;
	struct Node
	{
		T x;
		Node *next = nullptr;

		Node(const T x) noexcept : x(x) {}
	};
	size_t n = 0;
	Node *first = nullptr;

	~AlmostTree();

	void insert 	(const T x) 					noexcept;
	void del 		(const T x) 					noexcept;
	bool exists 	(const T x) 			const 	noexcept;
	bool next 		(const T x, T *next) 	const 	noexcept;
	bool prev 		(const T x, T *prev) 	const 	noexcept;
};
#endif