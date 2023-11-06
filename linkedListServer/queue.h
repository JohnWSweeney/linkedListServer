#pragma once
#include "nodes.h"
// sweeney's hand-rolled queue class.

class queue
{
public:
	int push(dNode* &list, int data);
	int pop(dNode** list);
	int front(dNode* list, int &data);
	int back(dNode* list, int &data);
	int clear(dNode** list);
	int isEmpty(dNode* list);
	int size(dNode* list, int &nodeCount);
	int print(dNode* list);
};

