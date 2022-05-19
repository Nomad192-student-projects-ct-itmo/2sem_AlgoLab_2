#ifndef ALMOSTTREE_H
#define	ALMOSTTREE_H

#include <cstdio>
#include <iostream>

class AlmostTree ///List
{
private:
	typedef TREE_TYPE T;
	typedef TREE_TYPE_SUM TS;
	struct Node
	{
		T x;
		Node *next = nullptr;

		Node(const T x) noexcept : x(x) {}
	};
	size_t n = 0;
	Node *first = nullptr;

public:
	~AlmostTree();

	bool 	insert 	(const T x) 					noexcept;
	bool 	del 	(const T x) 					noexcept;
	bool 	exists 	(const T x) 			const 	noexcept;
	bool 	next 	(const T x, T *next) 	const 	noexcept;
	bool 	prev 	(const T x, T *prev) 	const 	noexcept;
	TS 		sum 	(const T l, const T r)	const 	noexcept; 
};
#endif