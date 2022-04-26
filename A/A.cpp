#include <cstdio>

class AlmostTree
{
private:
	typedef unsigned int T;
public:
	struct Node
	{
		T x;
		size_t l;
		size_t r;
	};
private:
	size_t n;
	size_t current_add;
	Node *data;

public:
	AlmostTree(size_t n) : n(n), data(new Node[n]), current_add(0) {}
	~AlmostTree() {delete[] data;}

	void add(Node v)
	{
		if (current_add >= n) return;

		data[current_add++] = v;
	}

	bool check(size_t root)
	{
		return check_rq(root);
	}
	void print()
	{
		printf("Tree(");
		for(size_t i = 0; i < n - 1; i++)
			printf("%u, ", data[i].x);
		printf("%u)\n", data[n-1].x);
	}
private:
	bool check_rq(size_t el)
	{
		if(el == -2) return true;

		if(data[el].l != -2 && data[data[el].l].x >= data[el].x)
			return false;

		if(data[el].r != -2 && data[data[el].r].x <= data[el].x)
			return false;

		return check_rq(data[el].l) && check_rq(data[el].r);
	}
};

int main()
{
	size_t n;
    scanf("%zu\n", &n);

    AlmostTree tree(n);

    for (size_t i = 0; i < n; i++)
    {
        unsigned int x;
        size_t l, r;
        scanf("%u %zu %zu", &x, &l, &r);
        tree.add({x, --l, --r});
    }

    //tree.print();

    size_t root;
    scanf("%zu", &root);

    printf(tree.check(--root) ? "YES" : "NO");

	return 0;
}

///set
///mkdir build & cd build & cmake -G "MinGW Makefiles" ..

///build and run
///cmake --build . & a & del a.exe

///move
///cd 2sem_AlgoLab_2\A\build