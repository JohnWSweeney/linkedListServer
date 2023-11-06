#include "queue.h"
// sweeney's hand-rolled queue class.

int queue::push(dNode* &list, int data)
{
	if (list == nullptr)
	{
		dNode* newNode = new dNode();
		newNode->data = data;
		newNode->next = newNode;
		newNode->prev = newNode;
		list = newNode;
		return 0;
	}

	dNode* head = list;
	do {
		if (list->next == head)
		{
			dNode* newNode = new dNode();
			newNode->data = data;
			newNode->next = head;
			newNode->prev = list;
			list->next = newNode;
			head->prev = newNode;
			list = head;
			return 0;
		}
		list = list->next;
	} while (list != head);
}

int queue::pop(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* dummy = *list;
	// if the list contains only one node.
	if (dummy->next == dummy)
	{
		delete dummy;
		*list = nullptr;
		return 0;
	}
	else
	{
		dNode* newHead = dummy->next;
		dNode* tail = dummy->prev;
		newHead->prev = tail;
		tail->next = newHead;
		*list = newHead;
		return 0;
	}
}

int queue::front(dNode* list, int &data)
{
	if (list == nullptr)
	{
		return 1;
	}
	else
	{
		data = list->data;
		return 0;
	}
}

int queue::back(dNode* list, int &data)
{
	if (list == nullptr)
	{
		return 1;
	}
	else
	{
		data = list->prev->data;
		return 0;
	}
}

int queue::clear(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	do {
		dNode* dummy = *list;
		if (dummy->next != head)
		{
			*list = dummy->next;
			delete dummy;
			return 0;
		}
		else if (dummy->next == head)
		{
			delete dummy;
			*list = nullptr;
			return 0;
		}
	} while (*list != nullptr);
}

int queue::isEmpty(dNode* list)
{
	if (list == nullptr) return 1;
	else return 0;
}

int queue::size(dNode* list, int &nodeCount)
{
	if (list == nullptr)
	{
		nodeCount = 0;
		return 1;
	}

	dNode* head = list;
	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != head);
	return 0;
}

int queue::print(dNode* list)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	int tempPos = 0;
	std::cout << "#\tdata:\tcurr:\t\t\tnext:\t\t\tprev:\n";
	do {
		std::cout << tempPos << '\t' << list->data << '\t' << list << '\t' << list->next << '\t' << list->prev << '\n';
		++tempPos;
		list = list->next;
	} while (list != head);
	std::cout << '\n';
	return 0;
}