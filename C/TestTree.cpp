#include "TestTree.h"

void TestTree::add(Node v) noexcept
{
	if (current_add >= n) return;

	data[current_add++] = v;
}

bool TestTree::isTree(size_t root) const noexcept
{
	return isTree_rq(root);
}

void TestTree::print() const noexcept
{
	printf("Tree(");
	for(size_t i = 0; i < n - 1; i++)
		printf("%u, ", data[i].x);
	printf("%u)\n", data[n-1].x);
}

bool TestTree::isTree_rq(size_t el) const noexcept
{
	if(el == IND_NEU_VAL) return true;

	if(data[el].l != IND_NEU_VAL && data[data[el].l].x >= data[el].x)
		return false;

	if(data[el].r != IND_NEU_VAL && data[data[el].r].x <= data[el].x)
		return false;
	
	return isTree_rq(data[el].l) && isTree_rq(data[el].r);
}