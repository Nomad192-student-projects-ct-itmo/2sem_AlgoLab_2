#include "TestTree.hpp"

size_t TestTree::calc_max_deep(size_t n) const noexcept
{
	if(n < 2) return n;

	size_t cache[2], deep = 2;
	cache[0] = 0;
	cache[1] = 1;

	for (size_t i = 2; cache[(i-1)%2] < n; i++, deep++) {
	    cache[i%2] = cache[0] + cache[1] + 1;
	}

	return deep - 1;
}

void TestTree::add(Node v) noexcept
{
	if (current_add >= n) return;

	data[current_add++] = v;
}

bool TestTree::isTree(size_t root) const noexcept
{
	if(n == 0) return true;
	return isTree_rq(root, 1);
}

void TestTree::print() const noexcept
{
	printf("Tree(");
	for(size_t i = 0; i < n - 1; i++)
		printf("%u, ", data[i].x);
	printf("%u)\n", data[n-1].x);
}

bool TestTree::isTree_rq(size_t el, size_t deep) const noexcept
{
	if(el == IND_NEU_VAL) return true;
	if(deep > max_deep) {printf("Error deep, cur=%zu, max=%zu\n", deep, max_deep); return false;}

	if(data[el].l != IND_NEU_VAL && data[data[el].l].x >= data[el].x)
		{printf("Error l > cur\n"); return false;}

	if(data[el].r != IND_NEU_VAL && data[data[el].r].x <= data[el].x)
		{printf("Error r < cur\n"); return false;}
	
	return isTree_rq(data[el].l, deep + 1) && isTree_rq(data[el].r, deep + 1);
}