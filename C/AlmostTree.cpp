#include "AlmostTree.h"

AlmostTree::~AlmostTree() noexcept
{
	Node *cur = first;
	while(cur)
	{
		Node *next = cur->next;
		delete cur;
		cur = next;
	}
}

void AlmostTree::insert(const T x) noexcept
{
	Node *cur = first;
	while(cur)
	{
		if(cur->x == x) {return;}
		if(cur->next != nullptr)
		{
			cur->next = new Node(x);
			n++;
			return;
		}
	}
	first->next = new Node(x);
	n++;
}

void AlmostTree::del(const T x) noexcept
{
	Node *cur = first;
	while(cur)
	{
		if(cur->next && cur->next->x) {
			cur->next = cur->next->next;
			delete cur->next;
			n--;
			return;
		}
	}
	if(first->x == x)
	{
		delete first;
		n--;
		first = nullptr;
	}
}
bool AlmostTree::exists(const T x) const noexcept
{
	Node *cur = first;
	while(cur)
	{
		if(cur->x == x)
			return true;
		cur = cur->next;
	}
	return false;
}

bool AlmostTree::next(const T x, T *next) const noexcept
{
	Node *cur = first;
	T min = x;
	while(cur)
	{
		if (cur->x > x)
		{
			min = cur->x;
			cur = cur->next;
			break;
		}
		cur = cur->next;
	}
	if(min == x) {return false;}
	while(cur)
	{
		if (cur->x > x && cur->x < min)
			min = cur->x;
		cur = cur->next;
	}
	if(min == x) {return false;}
	*next = min;
	return true;
}

bool AlmostTree::prev(const T x, T *prev) const noexcept
{
	Node *cur = first;
	T max = x;
	while(cur)
	{
		if (cur->x < x)
		{
			max = cur->x;
			cur = cur->next;
			break;
		}
		cur = cur->next;
	}
	if(max == x) {return false;}
	while(cur)
	{
		if (cur->x < x && cur->x > max)
			max = cur->x;
		cur = cur->next;
	}
	if(max == x) {return false;}
	*prev = max;
	return true;
}