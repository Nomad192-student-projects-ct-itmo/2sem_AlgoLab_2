#ifndef TESTTREE_H
#define TESTTREE_H

#include <cstdio>

class TestTree
{
private:
	#define IND_NEU_VAL (-2)
	typedef TREE_TYPE T;
public:
	struct Node
	{
		T x;
		size_t l;
		size_t r;
	};
private:
	size_t n;
	size_t max_deep;
	size_t current_add = 0;
	Node *data;

public:
	TestTree(const size_t n) noexcept : n(n), max_deep(calc_max_deep(n)), data(new Node[n]) {}
	~TestTree() noexcept {delete[] data;}

	void add  		(const Node v) 				noexcept;
	bool isTree  	(const size_t root) const 	noexcept;
	void print 		() 					const 	noexcept;
private:
	size_t calc_max_deep(size_t n) const noexcept;
	bool isTree_rq(size_t el, size_t deep) const noexcept;
};

#endif