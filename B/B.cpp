#include <cstdio>

class BST
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
	struct Node *data;
	size_t current_add;
public:
	BST(size_t n) : n(n), data(new struct Node[n]), current_add(0) {}
	~BST() {delete[] data;}

	void add(T x)
	{
		//printf("add\n");
		if(current_add == 0)
		{
			data[current_add++] = Node{x, (size_t)-2, (size_t)-2};
			return;
		}
		//printf("add_rq\n");
		add_rq(x < data[0].x ? data[0].l : data[0].r, x, 0);
	}
	void full_print()
	{
		printf("%zu\n", n);
		full_print_rq(0);
		printf("%d", 0+1);
	}

private:
	void full_print_rq(size_t el)
	{
		if(el == (size_t)-2) return;
		printf("%u %d %d\n", data[el].x, data[el].l+1, data[el].r+1);
		full_print_rq(data[el].l);
		full_print_rq(data[el].r);
	}
	void add_rq(size_t el, T &x, size_t prev)
	{

		if(el == (size_t)-2)
		{
			data[current_add] = Node{x, (size_t)-2, (size_t)-2};
			x < data[prev].x ? (data[prev].l = current_add) : (data[prev].r = current_add);
			current_add++;
			return;
		}

		add_rq(x < data[el].x ? data[el].l : data[el].r, x, el);
	}
};


int main()
{
	size_t n;
	scanf("%zu\n", &n);

	BST bst(n);

	while(n--)
	{
		unsigned int x;
		scanf("%u", &x);
		bst.add(x);
	}

	bst.full_print();

	return 0;
}


/* 
 * set 
mkdir build & cd build & cmake -G "MinGW Makefiles" ..

* build and run
cmake --build . && (echo START & b)
echo return code: %errorlevel%

* or
..\..\run b

* move
cd 2sem_AlgoLab_2\B\build
*/