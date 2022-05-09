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
	size_t current_add = 0;
	Node *data;

public:
	TestTree(const size_t n) noexcept : n(n), data(new Node[n]) {}
	~TestTree() noexcept {delete[] data;}

	void add  		(const Node v) 				noexcept;
	bool isTree  	(const size_t root) const 	noexcept;
	void print 		() 					const 	noexcept;
private:
	bool isTree_rq 	(const size_t el) 	const 	noexcept;
};

#endif