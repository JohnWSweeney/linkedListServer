#include "deque.h"
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

node* deque::init(int data)
{
	node* newNode = new node();
	newNode->data = data;
	newNode->next = nullptr;
	return newNode;
}

int deque::front(node* list, int &data)
{
	if (list == nullptr) return 1; // list is empty.
	data = list->data;
	return 0;
}

int deque::back(node* list, int &data)
{
	if (list == nullptr) return 1; // list is empty.
	// find tail.
	do
	{
		if (list->next == nullptr)
		{
			data = list->data;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int deque::push_front(node** list, int data)
{
	if (*list == nullptr)
	{
		*list = this->init(data);
		return 0;
	}
	node* head = *list;
	node* newNode = new node();
	newNode->data = data;
	newNode->next = head;
	*list = newNode;
	return 0;
}

int deque::pop_front(node** list)
{
	if (*list == nullptr) return 1; // list is empty.
	// 
	node* head = *list;
	node* newHead = head->next;
	delete head;
	*list = newHead;
	return 0;
}

int deque::push_back(node** list, int data)
{
	// check if list is empty.
	if (*list == nullptr)
	{
		*list = this->init(data);
		return 0;
	}

	node* head = *list;
	// find tail node, append new node.
	do {
		node* curr = *list;
		if (curr->next == nullptr)
		{
			node* newNode = new node();
			newNode->data = data;
			curr->next = newNode;
			newNode->next = nullptr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != nullptr);
}

int deque::pop_back(node** list)
{
	if (*list == nullptr) return 1; // list is empty.

	node* head = *list;
	// first check if list has only one node.
	if (head->next == nullptr)
	{
		delete head;
		*list = nullptr;
		return 0;
	}
	// else, find and remove tail node.
	do {
		node* curr = *list;
		if (curr->next->next == nullptr)
		{
			delete curr->next;
			curr->next = nullptr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != nullptr);
}

int deque::clear(node** list)
{
	if (*list == nullptr) return 1; // list is empty.

	do {
		node* curr = *list;
		node* dummy = curr;
		*list = curr->next;
		delete dummy;
	} while (*list != nullptr);
	return 0;
}

int deque::size(node* list, int &nodeCount)
{
	if (list == nullptr) // list is empty.
	{
		nodeCount = 0;
		return 1;
	}

	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int deque::isEmpty(node* list)
{
	if (list == nullptr) return 1; // list is empty.
	else return 0; // list is not empty.
}

int deque::print(node* list)
{
	if (list == nullptr) return 1; // list is empty.

	int tempPos = 0;
	std::cout << "#\tdata:\tcurr:\t\t\tnext:\n";
	do {
		std::cout << tempPos << '\t' << list->data << '\t' << list << '\t' << list->next << '\n';
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	std::cout << '\n';
	return 0;
}