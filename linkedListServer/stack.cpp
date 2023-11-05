#include "stack.h"
// sweeney's hand-rolled stack class.

int stack::push(node** list, int data)
{
	if (*list == nullptr)
	{
		node* newNode = new node();
		newNode->data = data;
		newNode->next = nullptr;
		*list = newNode;
		return 0;
	}
	else
	{
		node* head = *list;
		node* newHead = new node();
		newHead->data = data;
		newHead->next = head;
		*list = newHead;
		return 0;
	}
}

int stack::pop(node** list)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	if (head->next == nullptr)
	{
		*list = nullptr;
		delete head;
		return 0;
	}
	else
	{
		*list = head->next;
		delete head;
		return 0;
	}
}

int stack::top(node* list, int &data)
{
	if (list == nullptr) return 1;
	else
	{
		data = list->data;
		return 0;
	}
}

int stack::clear(node** list)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	if (head->next == nullptr)
	{
		*list = nullptr;
		delete head;
		return 0;
	}

	do {
		node* dummy = *list;
		*list = dummy->next;
		delete dummy;
	} while (*list != nullptr);
	return 0;
}

int stack::isEmpty(node* list)
{
	if (list == nullptr) return 1;
	else return 0;
}

int stack::size(node* list, int &nodeCount)
{
	if (list == nullptr) return 1;

	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int stack::print(node* list)
{
	if (list == nullptr) return 1;

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