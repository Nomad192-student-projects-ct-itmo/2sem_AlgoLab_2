#include "AlmostTree.hpp"

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

bool AlmostTree::insert(const T x) noexcept
{
	if(!first)
	{
		first = new Node(x);
		n++;
		return true;
	}

	Node *cur = first;
	while(cur->next)
	{
		if(cur->x == x) {return false;}
		cur = cur->next;
	}
	if(cur->x == x) {return false;}
	cur->next = new Node(x);
	n++;
	return true;
}

bool AlmostTree::del(const T x) noexcept
{
	if(!first) return false;
	if(first->x == x) 
	{
		Node *new_next = first->next;
		delete first;
		first = new_next;
		n--;
		return true;
	}
	Node *cur = first;
	while(cur->next)
	{
		if(cur->next && cur->next->x == x) {
			Node *new_next =  cur->next->next;
			delete cur->next;
			cur->next = new_next;
			n--;
			return true;
		}
		cur = cur->next;
	}
	return false;
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