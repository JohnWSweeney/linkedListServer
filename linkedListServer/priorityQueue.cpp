#include "priorityQueue.h"
// sweeney's hand-rolled priority queue class.

node* priorityQueue::init(int data)
{
	node* newNode = new node();
	newNode->data = data;
	newNode->next = nullptr;
	return newNode;
}

int priorityQueue::sort(node** list)
{
	if (*list == nullptr) return 1; // list is empty.
	// check if list has only one node.
	node* head = *list;
	if (head->next == nullptr) return 5;
	// declare and initialize variables.
	node* sortedList = *list;
	node* unsortedList = *list;
	node* unsortedHead = *list;
	node* prev = nullptr;
	node* tempPrev = nullptr;
	node* temp = nullptr;
	bool firstSweep = true;
	//
	do {
		//
		prev = unsortedList;
		temp = unsortedHead;
		*list = unsortedList->next;
		do {
			node* curr = *list;
			if (this->isAscending == true) // sort ascending.
			{
				if (curr->data < temp->data)
				{
					tempPrev = prev;
					temp = curr;
				}
			}
			else // sort descending.
			{
				if (curr->data > temp->data)
				{
					tempPrev = prev;
					temp = curr;
				}
			}
			prev = curr;
			*list = curr->next;
		} while (*list != nullptr);
		//
		if (temp == unsortedHead)
		{
			unsortedHead = unsortedHead->next;
			unsortedList = unsortedHead;
		}
		else
		{
			tempPrev->next = temp->next;
		}
		//
		if (firstSweep == true)
		{
			firstSweep = false;
			temp->next = unsortedHead;
			sortedList = temp;
			head = sortedList;
		}
		else
		{
			sortedList->next = temp;
			temp->next = unsortedHead;
			sortedList = temp;
		}
	} while (unsortedHead->next != nullptr);
	*list = head;
	return 0;
}

int priorityQueue::top(node* list, int &data)
{
	if (list == nullptr) return 1; // list is empty.
	data = list->data;
	return 0;
}

int priorityQueue::set(node** list, bool boolean)
{
	if (boolean != this->isAscending)
	{
		this->isAscending = boolean;
		this->sort(list);
		return 0;
	}
	else return 1;
}

int priorityQueue::push(node** list, int data)
{
	if (*list == nullptr)
	{
		*list = this->init(data);
	}
	else
	{
		node* head = *list;
		node* newNode = new node();
		newNode->data = data;
		newNode->next = head;
		*list = newNode;
	}
	this->sort(list);
	return 0;
}

int priorityQueue::pop(node** list)
{
	if (*list == nullptr) return 1; // list is empty.

	node* dummy = *list;
	*list = dummy->next;
	delete dummy;
	return 0;
}

int priorityQueue::clear(node** list)
{
	if (*list == nullptr) return 1; // list is empty.
	// delete all nodes in list.
	do {
		node* dummy = *list;
		*list = dummy->next;
		delete dummy;
	} while (*list != nullptr);
	return 0;
}

int priorityQueue::isEmpty(node* list)
{
	if (list == nullptr) return 1; // list is empty.
	else return 0; // list is not empty.
}

int priorityQueue::size(node* list, int &nodeCount)
{
	if (list == nullptr) return 1; // list is empty.

	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int priorityQueue::print(node* list)
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