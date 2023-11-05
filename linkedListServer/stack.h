#pragma once
#include "nodes.h"
// sweeney's hand-rolled stack class.

class stack
{
public:
	int push(node** list, int data);
	int pop(node** list);
	int top(node* list, int &data);
	int clear(node** list);
	int isEmpty(node* list);
	int size(node* list, int &nodeCount);
	int print(node* list);
};