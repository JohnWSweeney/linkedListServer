#include "dList.h"
#include "random.h" // required for shuffle function.
// sweeney's hand-rolled doubly linked list.
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


dNode* dList::init(int data)
{
	dNode* newNode = new dNode();
	newNode->data = data;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	return newNode;
}

int dList::addNodeFront(dNode** list, int data)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	dNode* newHead = new dNode();
	newHead->data = data;
	newHead->next = head;
	newHead->prev = nullptr;
	head->prev = newHead;
	*list = newHead;
	return 0;
}

int dList::addNodeBack(dNode* list, int data)
{
	if (list == nullptr) return 1;

	do {
		if (list->next == nullptr)
		{
			dNode* newNode = new dNode();
			newNode->data = data;
			newNode->next = nullptr;
			newNode->prev = list;
			list->next = newNode;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
}

int dList::addNodeByPos(dNode** list, int pos, int data)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	// find pos in list.
	if (pos == 0) // if pos is head node.
	{
		dNode* newNode = new dNode();
		newNode->data = data;
		newNode->prev = nullptr;
		newNode->next = head;
		head->prev = newNode;
		*list = newNode;
		return 0;
	}
	else
	{
		// check if list has only one node.
		if (head->next == nullptr) return -1;
		*list = head->next; // skip head node.
		int tempPos = 1;
		do {
			dNode* curr = *list;
			if (tempPos == pos) // found pos.
			{
				dNode* before = curr->prev;
				dNode* after = curr->next;
				dNode* newNode = new dNode();
				newNode->data = data;
				before->next = newNode;
				newNode->prev = before;
				newNode->next = curr;
				curr->prev = newNode;
				curr->next = after;
				if (after != nullptr)
				{
					after->prev = curr;
				}
				*list = head;
				return 0;
			}
			++tempPos;
			*list = curr->next;
		} while (*list != nullptr);
		*list = head; // pos not in list, reset list.
		return -1;
	}
}

int dList::deleteNodeFront(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	// if the list contains only one node.
	if (head->next == nullptr)
	{
		delete head;
		*list = nullptr;
		return 0;
	}
	else
	{
		dNode* newHead = head->next;
		newHead->prev = nullptr;
		delete head;
		*list = newHead;
		return 0;
	}
}

int dList::deleteNodeBack(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	// if the list contains only one node.
	if (head->next == nullptr)
	{
		delete head;
		*list = nullptr;
		return 0;
	}

	do {
		dNode* curr = *list;
		if (curr->next->next == nullptr)
		{
			delete curr->next;
			curr->next = nullptr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (list != nullptr);
}

int dList::deleteNodeByPos(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	if (pos == 0)
	{
		if (head->next == nullptr)
		{
			delete head;
			*list = nullptr;
			return 0;
		}
		else
		{
			dNode* newHead = head->next;
			newHead->prev = nullptr;
			delete head;
			*list = newHead;
			return 0;
		}
	}

	int tempPos = 0;
	do {
		dNode* dummy = *list;
		if (tempPos == pos)
		{
			if (dummy->next == nullptr)
			{
				dummy->prev->next = nullptr;
				delete dummy;
				*list = head;
				return 0;
			}
			else
			{
				dNode* before = dummy->prev;
				dNode* after = dummy->next;
				delete dummy;
				before->next = after;
				after->prev = before;
				*list = head;
				return 0;
			}
		}
		++tempPos;
		*list = dummy->next;
	} while (*list != nullptr);
	*list = head;
	return -1;
}

int dList::deleteNodeByPtr(dNode** list, dNode* &ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	do {
		dNode* dummy = *list;
		if (*list == ptr)
		{
			if (dummy->prev == nullptr and dummy->next == nullptr) // list has only one node.
			{
				*list = nullptr;
			}
			else if (dummy->prev == nullptr) // first node
			{
				dNode* newHead = dummy->next;
				newHead->prev = nullptr;
				*list = newHead;
			}
			else if (dummy->next == nullptr) // last node.
			{
				dummy->prev->next = nullptr;
				*list = head;
			}
			else // between first and last nodes.
			{
				dNode* before = dummy->prev;
				dNode* after = dummy->next;
				before->next = after;
				after->prev = before;
				*list = head;
			}
			delete dummy;
			ptr = nullptr;
			return 0;
		}
		*list = dummy->next;
	} while (*list != nullptr);
	return -1;
}

int dList::deleteBeforePos(dNode** list, int pos)
{
	if (*list == nullptr) return 1;
	if (pos == 0) return 0; // invalid.

	dNode* head = *list;
	// pos == 0 is invalid, skip head node.
	if (head->next != nullptr)
	{
		*list = head->next;
	}
	// find pos in list.
	int tempPos = 1;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// detach list before pos.
			dNode* before = curr->prev;
			before->next = nullptr;
			curr->prev = nullptr;
			// delete detached list.
			dNode* temp = head;
			do {
				dNode* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != nullptr);
			// reassign head and reset list;
			head = curr;
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != nullptr);
	*list = head;
	return -1; // pos not in list.
}

int dList::deleteBeforePtr(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	if (ptr == head) return 0; // invalid.
	// ptr == head is invalid, skip ahead.
	if (head->next != nullptr)
	{
		*list = head->next;
	}
	// find ptr in list.
	do {
		dNode* curr = *list;
		if (curr == ptr)
		{
			// detach list before ptr.
			dNode* before = curr->prev;
			before->next = nullptr;
			curr->prev = nullptr;
			// delete detached list section.
			dNode* temp = head;
			do {
				dNode* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != nullptr);
			// reassign head and reset list.
			head = curr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != nullptr);
	//*list = head;
	return -1; // ptr not in list.
}

int dList::deleteAfterPos(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;

	int tempPos = 0;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail node or list has only one node.
			if (curr->next == nullptr)
			{
				*list = head;
				return 0;
			}
			// detach list after pos.
			dNode* temp = curr->next;
			curr->next = nullptr;
			// delete detached portion of list.
			do {
				dNode* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != nullptr);
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != nullptr);
	*list = head;
	return -1;
}

int dList::deleteAfterPtr(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;

	do {
		dNode* curr = *list;
		// find ptr in list.
		if (curr == ptr) // ptr is in list.
		{
			// check if ptr is tail node.
			if (curr->next == nullptr)
			{
				*list = head;
				return 0;
			}
			// else, detach list after ptr.
			dNode* temp = curr->next;
			curr->next = nullptr;
			// delete detached portion of list.
			do {
				dNode* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != nullptr);
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != nullptr);
	*list = head;
	return -1; // ptr not in list.
}

int dList::returnPtrByPos(dNode* list, int pos, dNode* &ptr)
{
	if (list == nullptr) return 1;

	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			ptr = list;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::returnPosByPtr(dNode* list, int &pos, dNode* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	int tempPos = 0;
	do {
		if (list == ptr)
		{
			pos = tempPos;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::returnFrontData(dNode* list, int &data)
{
	if (list == nullptr) return 1; // list is empty.
	data = list->data;
	return 0;
}

int dList::returnBackData(dNode* list, int &data)
{
	if (list == nullptr) return 1; // list is empty.
	// find tail node, return data.
	do {
		if (list->next == nullptr)
		{
			data = list->data;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
}

int dList::returnDataByPos(dNode* list, int &data, int pos)
{
	if (list == nullptr) return 1;

	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			data = list->data;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::returnDataByPtr(dNode* list, int &data, dNode* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	do {
		if (list = ptr)
		{
			data = list->data;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::updateDataByPos(dNode* list, int data, int pos)
{
	if (list == nullptr) return 1;

	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			list->data = data;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::updateDataByPtr(dNode* list, int data, dNode* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	do {
		if (list == ptr)
		{
			list->data = data;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::findDataReturnPos(dNode* list, int data, int &pos)
{
	if (list == nullptr) return 1;

	int tempPos = 0;
	do {
		if (list->data == data)
		{
			pos = tempPos;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::findDataReturnPtr(dNode* list, int data, dNode* &ptr)
{
	if (list == nullptr) return 1;

	do {
		if (list->data == data)
		{
			ptr = list;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
	return -1;
}

int dList::findMinReturnPos(dNode* list, int &min, int &pos)
{
	if (list == nullptr) return 1;

	min = list->data;
	pos = 0;
	list = list->next;

	int tempPos = 1;
	do {
		if (min > list->data)
		{
			min = list->data;
			pos = tempPos;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int dList::findMinReturnPtr(dNode* list, int &min, dNode* &ptr)
{
	if (list == nullptr) return 1;

	min = list->data;
	ptr = list;
	list = list->next;

	do {
		if (min > list->data)
		{
			min = list->data;
			ptr = list;
		}
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int dList::findMaxReturnPos(dNode* list, int &max, int &pos)
{
	if (list == nullptr) return 1;

	max = list->data;
	pos = 0;
	list = list->next;

	int tempPos = 1;
	do {
		if (max < list->data)
		{
			max = list->data;
			pos = tempPos;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int dList::findMaxReturnPtr(dNode* list, int &max, dNode* &ptr)
{
	if (list == nullptr) return 1;

	max = list->data;
	ptr = list;
	list = list->next;

	do {
		if (max < list->data)
		{
			max = list->data;
			ptr = list;
		}
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int dList::findTailReturnPos(dNode* list, int &pos)
{
	if (list == nullptr) return 1;

	int tempPos = 0;
	do {
		if (list->next == nullptr)
		{
			pos = tempPos;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != nullptr);
}

int dList::findTailReturnPtr(dNode* list, dNode* &ptr)
{
	if (list == nullptr) return 1;

	do {
		if (list->next == nullptr)
		{
			ptr = list;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
}

int dList::movePosToFront(dNode** list, int pos)
{
	if (*list == nullptr) return 1;
	if (pos == 0) return -2; // no action needed.

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr)
	{
		return 5;
	}
	// no action on pos == 0, skip head.
	*list = head->next;
	// find pos in list.
	int tempPos = 1;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			dNode* before = curr->prev;
			dNode* after = curr->next;
			before->next = after;
			// check if pos is tail.
			if (after != nullptr)
			{
				after->prev = before;
			}
			curr->next = head;
			head->prev = curr;
			*list = curr;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != nullptr);
	*list = head; // pos not in list.
	return -1;
}

int dList::movePtrToFront(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	if (ptr == head) return 0;

	do {
		dNode* curr = *list;
		if (curr->next == ptr)
		{
			dNode* after = ptr->next;
			curr->next = after;
			if (after != nullptr)
			{
				after->prev = curr;
			}
			head->prev = ptr;
			ptr->next = head;
			ptr->prev = nullptr;
			*list = ptr;
			return 0;
		}
		*list = curr->next;
	} while (*list != nullptr);
	return -1;
}

int dList::movePosToBack(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr) return 5;
	// declare variables.
	dNode* prev = head; // ptr to node before pos node.
	dNode* posNode = head; // ptr to pos node.
	dNode* temp = head; // hold previous node b/w sweeps.
	dNode* tail = head;
	// find pos in list.
	bool foundPos = false;
	int tempPos = 0;
	do {
		dNode* curr = *list;
		if (tempPos == pos) // found pos.
		{
			// check if pos is tail.
			if (curr->next == nullptr)
			{
				*list = head;
				return -2; // no action needed.
			}
			foundPos = true;
			prev = temp;
			posNode = curr;
		}
		if (curr->next == nullptr) // find tail.
		{
			tail = curr;
		}
		++tempPos;
		temp = curr;
		*list = curr->next;
	} while (*list != nullptr);

	if (foundPos == true)
	{
		if (posNode == head)
		{
			head = head->next;
			tail->next = posNode;
			posNode->next = nullptr;
		}
		else
		{
			prev->next = posNode->next;
			tail->next = posNode;
			posNode->next = nullptr;
		}
		*list = head;
		return 0;
	}
	else
	{
		*list = head; // pos not in list, reset list.
		return -1;
	}
}

int dList::movePtrToBack(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	bool foundPtr = false;
	dNode* curr = nullptr;
	dNode* tail = nullptr;
	do {
		curr = *list;
		// list has only one node or desired node is tail.
		if (curr == ptr and curr->next == nullptr)
		{
			*list = head;
			return 0;
		}
		// desired node is not tail.
		else if (curr == ptr and curr->next != nullptr)
		{
			foundPtr = true;
			dNode* after = curr->next;
			if (ptr == head) // if desired node is head.
			{
				head = after;
				after->prev = nullptr;
			}
			else
			{
				dNode* before = curr->prev;
				before->next = after;
				after->prev = before;
			}
		}
		// find tail node.
		if (curr->next == nullptr)
		{
			tail = curr;
		}
		*list = curr->next;
	} while (*list != nullptr);

	if (foundPtr == true)
	{
		tail->next = ptr;
		ptr->prev = tail;
		ptr->next = nullptr;
		*list = head;
		return 0;
	}
	else
	{
		*list = head;
		return -1;
	}
}

int dList::movePosUp(dNode** list, int pos)
{
	if (*list == nullptr) return 1; // list empty.
	if (pos == 0) return -2; // no action needed.

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr) return 5;
	// no action on pos == 0, skip head.
	*list = head->next;
	// find pos in list.
	int tempPos = 1;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			dNode* before = curr->prev->prev;
			dNode* prev = curr->prev;
			dNode* after = curr->next;
			if (curr->prev == head)
			{
				curr->prev = nullptr;
				head = curr;
			}
			else
			{
				before->next = curr;
				curr->prev = before;
			}
			curr->next = prev;
			prev->prev = curr;
			prev->next = after;
			if (after != nullptr)
			{
				after->prev = prev;
			}
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != nullptr);
	*list = head; // pos not in list.
	return -1;
}

int dList::movePtrUp(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	if (ptr == head) return 0;

	dNode* before = nullptr;
	dNode* newPos = nullptr; // new ptr position.
	dNode* curr = nullptr; // current ptr position.
	dNode* after = nullptr;
	do {
		curr = *list;
		// if desired node is second in list.
		if (curr == ptr and curr->prev == head)
		{
			after = curr->next;
			curr->prev = nullptr;
			curr->next = head;
			head->prev = curr;
			if (after != nullptr) // if list more than two nodes.
			{
				after->prev = head;
			}
			head->next = after;
			head = curr;
			*list = head;
			return 0;
		}
		// if desired node is b/w head and tail.
		else if (curr == ptr and curr->next != nullptr)
		{
			before = curr->prev->prev;
			newPos = curr->prev;
			after = curr->next;
			before->next = curr;
			curr->prev = before;
			curr->next = newPos;
			newPos->prev = curr;
			newPos->next = after;
			after->prev = newPos;
			*list = head;
			return 0;
		}
		// if desired node is tail.
		else if (curr == ptr and curr->next == nullptr)
		{
			before = curr->prev->prev;
			newPos = curr->prev;
			before->next = curr;
			curr->prev = before;
			curr->next = newPos;
			newPos->prev = curr;
			newPos->next = nullptr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != nullptr);
	return -1;
}

int dList::movePosDown(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr) return 5;
	// find pos in list.
	int tempPos = 0;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail.
			if (curr->next == nullptr)
			{
				*list = head;
				return -2; // no action needed.
			}
			dNode* before = curr->prev; // node before swapped nodes.
			dNode* next = curr->next; // node after pos in original list.
			dNode* after = curr->next->next; // node after swapped nodes.
			if (curr == head)
			{
				next->prev = nullptr;
				head = next;
			}
			else
			{
				before->next = next;
				next->prev = before;
			}
			next->next = curr;
			curr->prev = next;
			curr->next = after;
			if (after != nullptr)
			{
				after->prev = curr;
			}
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != nullptr);
	*list = head; // pos not in list.
	return -1;
}

int dList::movePtrDown(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	dNode* before = nullptr;
	dNode* newPos = nullptr; // new ptr position.
	dNode* curr = nullptr; // current ptr position.
	dNode* after = nullptr;
	bool foundPtr = false;
	do {
		dNode* curr = *list;
		if (curr == ptr)
		{
			// ptr is tail node or list has only one node.
			if (curr->next == nullptr)
			{
				*list = head;
				return 0;
			}
			// ptr is head node.
			else if (curr == head)
			{
				newPos = curr->next; // new head.
				after = curr->next->next;
				newPos->prev = nullptr;
				newPos->next = curr;
				curr->prev = newPos;
				curr->next = after;
				if (after != nullptr) // if list more than two nodes.
				{
					after->prev = curr;
				}
				head = newPos;
				*list = head;
				return 0;
			}
			// ptr is second to last node.
			else if (curr->next->next == nullptr)
			{
				before = curr->prev;
				newPos = curr->next;
				before->next = newPos;
				newPos->prev = before;
				newPos->next = curr;
				curr->prev = newPos;
				curr->next = nullptr;
				*list = head;
				return 0;
			}
			// ptr is between head and tail nodes.
			else
			{
				before = curr->prev;
				newPos = curr->next;
				after = curr->next->next;
				before->next = newPos;
				newPos->prev = before;
				newPos->next = curr;
				curr->prev = newPos;
				curr->next = after;
				after->prev = curr;
				*list = head;
				return 0;
			}

		}
		*list = curr->next;
	} while (*list != nullptr);
	return -1;
}

int dList::clear(dNode** list)
{
	if (*list == nullptr) return 1;

	do {
		dNode* dummy = *list;
		*list = dummy->next;
		delete dummy;
	} while (*list != nullptr);
	return 0;
}

int dList::size(dNode* list, int &nodeCount)
{
	if (list == nullptr) return 1;

	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != nullptr);
	return 0;
}

int dList::isEmpty(dNode* list)
{
	if (list == nullptr) return 1;
	else return 0;
}

int dList::print(dNode* list)
{
	if (list == nullptr) return 1;

	int tempPos = 0;
	std::cout << "#\tdata:\tcurr:\t\t\tnext:\t\t\tprev:\n";
	do {
		std::cout << tempPos << '\t' << list->data << '\t' << list << '\t' << list->next << '\t' << list->prev << '\n';
		++tempPos;
		list = list->next;
	} while (list != nullptr);
	std::cout << '\n';
	return 0;
}

int dList::reverse(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* tail = *list;
	*list = tail->next;
	tail->next = nullptr;

	dNode* curr = nullptr;
	do {
		curr = *list;
		dNode* temp = curr->next;
		curr->next = tail;
		tail->prev = curr;
		tail = curr;
		*list = temp;
	} while (*list != nullptr);
	*list = curr;
	return 0;
}

int dList::swap(dNode** list, dNode* ptr1, dNode* ptr2)
{
	if (*list == nullptr) return 1;
	if (ptr1 == nullptr or ptr2 == nullptr) return 2;
	//if (ptr2 == nullptr) return 3;
	if (ptr1 == ptr2) return -2; // no action needed.

	dNode* head = *list;
	// check if list has only only node.
	if (head->next == nullptr) return 5;
	// find ptr1 and ptr2 in list.
	bool foundPtr1 = false;
	bool foundPtr2 = false;
	do {
		dNode* curr = *list;
		if (curr == ptr1)
		{
			foundPtr1 = true;
		}
		if (curr == ptr2)
		{
			foundPtr2 = true;
		}
		*list = curr->next;
	} while (*list != nullptr);

	if (foundPtr1 == true and foundPtr2 == true)
	{
		dNode* before1 = ptr1->prev; // node before ptr1.
		dNode* after1 = ptr1->next; // node after ptr1.
		dNode* before2 = ptr2->prev; // node before ptr2.
		dNode* after2 = ptr2->next; // node after ptr2.

		// check if either node is head.
		if (ptr1 == head)
		{
			ptr2->prev = nullptr;
			head = ptr2;
		}
		else if (ptr2 == head)
		{
			ptr1->prev = nullptr;
			head = ptr1;
		}

		// check if ptr1 and ptr2 are adjacent.
		if (ptr1->next == ptr2)
		{
			if (before1 != nullptr)
			{
				before1->next = ptr2;
			}
			ptr2->prev = before1;
			ptr2->next = ptr1;
			ptr1->prev = ptr2;
			ptr1->next = after2;
			if (after2 != nullptr)
			{
				after2->prev = ptr1;
			}
		}
		else if (ptr2->next == ptr1)
		{
			if (before2 != nullptr)
			{
				before2->next = ptr1;
			}
			ptr1->prev = before2;
			ptr1->next = ptr2;
			ptr2->prev = ptr1;
			ptr2->next = after1;
			if (after1 != nullptr)
			{
				after1->prev = ptr2;
			}
		}
		else // ptr1 and ptr2 not adjacent.
		{
			if (before1 != nullptr)
			{
				before1->next = ptr2;
			}
			ptr2->prev = before1;
			ptr2->next = after1;
			if (after1 != nullptr)
			{
				after1->prev = ptr2;
			}

			if (before2 != nullptr)
			{
				before2->next = ptr1;
			}
			ptr1->prev = before2;
			ptr1->next = after2;
			if (after2 != nullptr)
			{
				after2->prev = ptr1;
			}
		}
		*list = head;
		return 0;
	}
	else // pos not in list, reset list.
	{
		*list = head;
		return -1;
	}
}

int dList::shuffle(dNode** list)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr) return 5;

	random random;
	random.initMt();

	int nodeCount;
	int result = size(*list, nodeCount);
	int position1 = 0;
	int position2 = 0;
	int temp = 0;
	// swap random positions nodeCount^2 number of times.
	do {
		// swap two randomly selected positions.
		do {
			position1 = random.getNum(0, nodeCount - 1);
			position2 = random.getNum(0, nodeCount - 1);
		} while (position1 == position2);

		dNode* ptr1 = nullptr;
		dNode* ptr2 = nullptr;
		returnPtrByPos(*list, position1, ptr1);
		returnPtrByPos(*list, position2, ptr2);
		swap(list, ptr1, ptr2);
		++temp;
	} while (temp < pow(nodeCount, 2));
	return 0;
}

int dList::bubbleSort(dNode** list, bool isAscending, int &swapCount, int &sweepCount)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr) return 5;
	// declare and initialize variables.
	dNode* before = nullptr; // node before adjacent nodes under test.
	dNode* curr = nullptr; // first adjacent node under test.
	dNode* test = nullptr; // second adjacent node under test.
	dNode* after = nullptr; // node after adjacent nodes under test.
	int swaps = 0;
	swapCount = 0;
	sweepCount = 0;
	// sweep list, swap adjacent nodes according to isAscending.
	// stop on first sweep with no swaps.
	do {
		// sweep list, swapping adajcent nodes as needed.
		swaps = 0;
		do {
			curr = *list;
			before = curr->prev;
			test = curr->next;
			after = curr->next->next;
			if (isAscending == true) // sort ascending.
			{
				if (curr->data > test->data)
				{
					if (curr == head)
					{
						head = test;
						test->prev = nullptr;
					}
					else
					{
						before->next = test;
						test->prev = before;
					}
					test->next = curr;
					curr->prev = test;
					curr->next = after;
					if (after != nullptr)
					{
						after->prev = curr;
					}
					*list = curr;
					++swaps;
				}
				else
				{
					*list = curr->next;
				}
			}
			else // sort descending.
			{
				if (curr->data < test->data)
				{
					if (curr == head)
					{
						head = test;
						test->prev = nullptr;
					}
					else
					{
						before->next = test;
						test->prev = before;
					}
					test->next = curr;
					curr->prev = test;
					curr->next = after;
					if (after != nullptr)
					{
						after->prev = curr;
					}
					*list = curr;
					++swaps;
				}
				else
				{
					*list = curr->next;
				}
			}
		} while (after != nullptr);
		swapCount += swaps;
		++sweepCount;
		*list = head; // reset list.

	} while (swaps != 0);
	return 0;
}

int dList::selectionSort(dNode** list, bool isAscending)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == nullptr) return 5;
	// declare and initialze variables.
	dNode* sortedList = *list; // sorted portion of list.
	dNode* unsortedList = *list; // unsorted portion of list.
	dNode* unsortedHead = *list; // first node in unsorted list.
	dNode* temp = nullptr; // hold min/max for current sweep.
	bool firstSweep = true;
	// sweep-sort list until unsortedHead is the last node.
	do {
		// find min/max node, place in sorted list.
		temp = unsortedHead; // initialize with unsortedHead.
		*list = unsortedList->next;
		do {
			dNode* curr = *list;
			if (isAscending == true) // sort list ascending.
			{
				if (curr->data < temp->data)
				{
					temp = curr;
				}
			}
			else // sort list descending.
			{
				if (curr->data > temp->data)
				{
					temp = curr;
				}
			}
			*list = curr->next;
		} while (*list != nullptr);

		if (temp == unsortedHead)
		{
			unsortedHead = unsortedHead->next;
			unsortedList = unsortedHead;
		}
		else
		{
			dNode* before = temp->prev;
			dNode* after = temp->next;
			if (before != nullptr)
			{
				before->next = after;
			}
			if (after != nullptr)
			{
				after->prev = before;
			}
		}
		// on first sweep put temp at front of sorted list.
		if (firstSweep == true)
		{
			firstSweep = false;
			temp->prev = nullptr;
			temp->next = unsortedHead;
			unsortedHead->prev = temp;
			sortedList = temp;
			head = sortedList;
		}
		else // afterward, concatenate temp nodes in sorted list.
		{
			temp->prev = sortedList;
			sortedList->next = temp;
			temp->next = unsortedHead;
			unsortedHead->prev = temp;
			sortedList = temp;
		}

	} while (unsortedHead->next != nullptr);
	*list = head;
	return 0;
}