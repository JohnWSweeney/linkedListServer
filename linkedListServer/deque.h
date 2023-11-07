#pragma once
#include "nodes.h"
// sweeney's hand-rolled deque class.
//
// pos = "position".
// ptr = "pointer".
//
// error codes:
// 0	no error.
// 1	list is nullptr.
// 2	ptr is nullptr.
// 5	list has only one node.
// -1	pos/ptr not in list.
// -2	no action needed.

class deque
{
private:
	node* init(int data);
public:
	int front(node* list, int &data);
	int back(node* list, int &data);
	int push_front(node** list, int data);
	int pop_front(node** list);
	int push_back(node** list, int data);
	int pop_back(node** list);
	int clear(node** list);
	int size(node*, int &nodeCount);
	int isEmpty(node*);
	int print(node* list);
};