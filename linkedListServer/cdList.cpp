#include "cdList.h"
#include "random.h" // required for shuffle function.
// sweeney's hand-rolled circular doubly linked list.
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

dNode* cdList::init(int data)
{
	dNode* newNode = new dNode();
	newNode->data = data;
	newNode->next = newNode;
	newNode->prev = newNode;
	return newNode;
}

int cdList::addNodeFront(dNode** list, int data)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	dNode* tail = head->prev;
	dNode* newHead = new dNode();
	newHead->data = data;
	tail->next = newHead;
	newHead->prev = tail;
	newHead->next = head;
	head->prev = newHead;
	*list = newHead;
	return 0;
}

int cdList::addNodeBack(dNode* list, int data)
{
	if (list == nullptr) return 1;

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
			return 0;
		}
		list = list->next;
	} while (list != head);
}

int cdList::addNodeByPos(dNode** list, int pos, int data)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	dNode* tail = head->prev;
	// find pos in list.
	if (pos == 0) // found pos.
	{
		dNode* newNode = new dNode();
		newNode->data = data;
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = head;
		head->prev = newNode;
		*list = newNode; // assign new head node.
		return 0;
	}
	else
	{
		// check is list has only one node.
		if (head->next == head) return -1;
		*list = head->next; // skip head.
		int tempPos = 1;
		do {
			dNode* curr = *list;
			if (tempPos == pos) // found pos.
			{
				dNode* before = curr->prev;
				dNode* newNode = new dNode();
				newNode->data = data;
				before->next = newNode;
				newNode->prev = before;
				newNode->next = curr;
				curr->prev = newNode;
				*list = head;
				return 0;
			}
			++tempPos;
			*list = curr->next;
		} while (*list != head);
		*list = head; // pos not in list, reset list.
		return -1;
	}
}

int cdList::deleteNodeFront(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* dummy = *list;
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

int cdList::deleteNodeBack(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	do {
		dNode* dummy = *list;
		// if the list contains only one node.
		if (dummy->next == head and dummy->prev == head)
		{
			delete dummy;
			*list = nullptr;
			return 0;
		}
		else if (dummy->next->next == head)
		{
			delete dummy->next;
			dummy->next = head;
			head->prev = dummy;
			*list = head;
			return 0;
		}
		*list = dummy->next;
	} while (*list != head);
}

int cdList::deleteNodeByPos(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	int tempPos = 0;
	do {
		dNode* dummy = *list;
		// if the list contains only one node.
		if (dummy->next == dummy)
		{
			delete dummy;
			*list = nullptr;
			return 0;
		}
		else if (tempPos == pos)
		{
			dNode* before = dummy->prev;
			dNode* after = dummy->next;
			delete dummy;
			before->next = after;
			after->prev = before;
			if (pos == 0)
			{
				*list = after;
			}
			else
			{
				*list = head;
			}
			return 0;
		}
		++tempPos;
		*list = dummy->next;
	} while (*list != head);
	return -1;
}

int cdList::deleteNodeByPtr(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	do {
		dNode* dummy = *list;
		if (dummy == ptr)
		{
			dNode* before = dummy->prev;
			dNode* after = dummy->next;
			before->next = after;
			after->prev = before;
			if (dummy == head) // check if node to be deleted is head.
			{
				head = after;
			}
			delete dummy;
			*list = head;
			return 0;
		}
		*list = dummy->next;
	} while (*list != head);
	return -1;
}

int cdList::deleteBeforePos(dNode** list, int pos)
{
	if (*list == nullptr) return 1;
	if (pos == 0) return 0; // invalid.

	dNode* head = *list;
	dNode* tail = head->prev;
	// pos == 0 is invalid, skip head.
	if (head->next != head)
	{
		*list = head->next;
	}

	// find pos in list.
	int tempPos = 1;
	do {
		dNode* curr = *list;
		if (tempPos == pos) // found pos.
		{
			// detach list before pos.
			dNode* before = curr->prev;
			before->next = nullptr;
			head->prev = nullptr;
			// assign new head, connect to tail.
			dNode* newHead = curr;
			newHead->prev = tail;
			tail->next = newHead;
			// delete detached list.
			*list = head;
			do {
				curr = *list;
				dNode* dummy = curr;
				*list = curr->next;
				delete dummy;
			} while (*list != nullptr);
			*list = newHead;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != head);
	*list = head; // pos not in list, reset list.
	return -1;
}

int cdList::deleteBeforePtr(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	dNode* tail = head->prev;
	if (ptr == head) return 0; // invalid.
	// ptr == head invalid, skip head.
	if (head->next != head)
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
			head->prev = nullptr;
			// assign new head, connect to tail.
			dNode* newHead = curr;
			newHead->prev = tail;
			tail->next = newHead;
			// delete detached list.
			*list = head;
			do {
				curr = *list;
				dNode* dummy = curr;
				*list = curr->next;
				delete dummy;
			} while (*list != nullptr);
			*list = newHead;
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
	*list = head; // ptr not in list, reset list.
	return -1;
}

int cdList::deleteAfterPos(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	int tempPos = 0;
	// find pos in list.
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail node.
			if (curr->next == head)
			{
				*list = head;
				return 0;
			}
			// else, detach list after pos.
			dNode* temp = curr->next;
			curr->next = head;
			head->prev = curr;
			// delete detached list.
			do {
				dNode* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != head);
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != head);
	*list = head; // pos not in list, reset list.
	return -1;
}

int cdList::deleteAfterPtr(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	// find ptr in list.
	do {
		dNode* curr = *list;
		if (curr == ptr)
		{
			// check if ptr is tail node.
			if (curr->next == head)
			{
				*list = head;
				return 0;
			}
			// else, detach list after ptr.
			dNode* temp = curr->next;
			// connect head and new tail node.
			curr->next = head;
			head->prev = curr;
			// delete detached list.
			do {
				dNode* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != head);
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
	*list = head; // ptr not in list, reset list.
	return -1;
}

int cdList::returnPtrByPos(dNode* list, int pos, dNode* &ptr)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			ptr = list;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::returnPosByPtr(dNode* list, int &pos, dNode* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = list;
	int tempPos = 0;
	do {
		if (list == ptr)
		{
			pos = tempPos;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::returnDataByPos(dNode* list, int &data, int pos)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			data = list->data;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::returnDataByPtr(dNode* list, int &data, dNode* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = list;
	do {
		if (list == ptr)
		{
			data = list->data;
			return 0;
		}
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::updateDataByPos(dNode* list, int data, int pos)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	int tempPos = 0;
	do {
		if (tempPos == pos)
		{
			list->data = data;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::updateDataByPtr(dNode* list, int data, dNode* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = list;
	do {
		if (list == ptr)
		{
			list->data = data;
			return 0;
		}
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::findDataReturnPos(dNode* list, int data, int &pos)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	int tempPos = 0;
	do {
		if (list->data == data)
		{
			pos = tempPos;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::findDataReturnPtr(dNode* list, int data, dNode* &ptr)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	do {
		if (list->data == data)
		{
			ptr = list;
			return 0;
		}
		list = list->next;
	} while (list != head);
	return -1;
}

int cdList::findMinReturnPos(dNode* list, int &min, int &pos)
{
	if (list == nullptr) return 1;

	dNode* head = list;

	min = list->data;
	pos = 0;
	list = list->next;

	int tempPos = 1;
	do {
		if (list->data < min)
		{
			min = list->data;
			pos = tempPos;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return 0;
}

int cdList::findMinReturnPtr(dNode* list, int &min, dNode* &ptr)
{
	if (list == nullptr) return 1;

	dNode* head = list;

	min = list->data;
	ptr = list;
	list = list->next;
	do {
		if (list->data < min)
		{
			min = list->data;
			ptr = list;
		}
		list = list->next;
	} while (list != head);
	return 0;
}

int cdList::findMaxReturnPos(dNode* list, int &max, int &pos)
{
	if (list == nullptr) return 1;

	dNode* head = list;

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
	} while (list != head);
	return 0;
}

int cdList::findMaxReturnPtr(dNode* list, int &max, dNode* &ptr)
{
	if (list == nullptr) return 1;

	dNode* head = list;

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
	} while (list != head);
	return 0;
}

int cdList::findTailReturnPos(dNode* list, int &pos)
{
	if (list == nullptr) return 1;
	dNode* head = list;
	int tempPos = 0;
	do {
		if (list->next == head)
		{
			pos = tempPos;
			return 0;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
}

int cdList::findTailReturnPtr(dNode* list, dNode* &ptr)
{
	if (list == nullptr) return 1;
	dNode* tail = list->prev;
	ptr = tail;
	return 0;
}

int cdList::movePosToFront(dNode** list, int pos)
{
	if (*list == nullptr) return 1; // list empty.
	if (pos == 0) return -2; // no action needed.

	dNode* head = *list;
	dNode* tail = head->prev;
	// check if list has only one node.
	if (head->next == head) return 5;
	// pos == 0 invalid, skip head.
	*list = head->next;
	// find pos in list.
	int tempPos = 1;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail.
			if (curr->next == head)
			{
				// rotate list forward one node.
				*list = tail;
				return 0;
			}
			dNode* before = curr->prev;
			dNode* after = curr->next;
			tail->next = curr;
			curr->prev = tail;
			curr->next = head;
			head->prev = curr;
			before->next = after;
			after->prev = before;
			*list = curr;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != head);
	*list = head; // pos not in list, reset list.
	return -1;
}

int cdList::movePtrToFront(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	dNode* tail = head->prev;
	if (ptr == head) return 0;
	else if (ptr == tail)
	{
		head = tail;
		*list = head;
		return 0;
	}

	do {
		dNode* curr = *list;
		if (curr == ptr)
		{
			dNode* before = curr->prev;
			dNode* after = curr->next;
			before->next = after;
			after->prev = before;
			ptr->next = head;
			ptr->prev = tail;
			head->prev = ptr;
			tail->next = ptr;
			head = ptr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
	return -1;
}

int cdList::movePosToBack(dNode** list, int pos)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	dNode* tail = head->prev;
	// check if list has only one node.
	if (head->next == head) return 5;
	// find pos in list.
	int tempPos = 0;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail.
			if (curr->next == head)
			{
				*list = head;
				return -2; // no action needed.
			}
			else if (curr == head)
			{
				head = head->next;
			}
			dNode* before = curr->prev;
			dNode* after = curr->next;
			before->next = after;
			after->prev = before;
			tail->next = curr;
			curr->prev = tail;
			curr->next = head;
			head->prev = curr;
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != head);
	*list = head; // pos not in list, reset list.
	return -1;
}

int cdList::movePtrToBack(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	dNode* tail = head->prev;
	if (ptr == head)
	{
		head = ptr->next;
		*list = head;
		return 0;
	}
	else if (ptr == tail) return 0;

	do {
		dNode* curr = *list;
		if (curr == ptr)
		{
			dNode* before = curr->prev;
			dNode* after = curr->next;
			before->next = after;
			after->prev = before;
			ptr->next = head;
			ptr->prev = tail;
			tail->next = ptr;
			head->prev = ptr;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
	return -1;
}

int cdList::movePosUp(dNode** list, int pos)
{
	if (*list == nullptr) return 1; // list empty.
	if (pos == 0) return -2; // no action needed.

	dNode* head = *list;
	dNode* tail = head->prev;
	// check if list has only one node.
	if (head->next == head) return 5;
	// pos == 0 invalid, skip head.
	*list = head->next;
	// find pos in list.
	int tempPos = 1;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			dNode* before = curr->prev->prev; // node before swapped nodes.
			dNode* prev = curr->prev; // node previous to pos in original list.
			dNode* after = curr->next; // node after swapped nodes.

			if (prev == head)
			{
				head = curr;
			}
			// check if list has only two nodes.
			if (prev != after) // list has more than two nodes.
			{
				before->next = curr;
				curr->prev = before;
				curr->next = prev;
				prev->prev = curr;
				prev->next = after;
				after->prev = prev;
			}
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != head);
	*list = head; // pos not in list, reset list.
	return -1;
}

int cdList::movePtrUp(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	if (ptr == head) return 0;

	do {
		dNode* curr = *list;
		if (curr->next == ptr)
		{
			dNode* before = curr->prev;
			dNode* after = ptr->next;
			before->next = ptr;
			ptr->prev = before;
			ptr->next = curr;
			curr->prev = ptr;
			curr->next = after;
			after->prev = curr;
			if (curr == head)
			{
				*list = ptr;
			}
			else
			{
				*list = head;
			}
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
	return -1;
}

int cdList::movePosDown(dNode** list, int pos)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	dNode* tail = head->prev;
	// check if list has only one node.
	if (head->next == head) return 5; // no action needed.
	// find pos in list.
	int tempPos = 0;
	do {
		dNode* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail.
			if (curr->next == head)
			{
				*list = head; // reset list.
				return -2; // no action needed.
			}

			dNode* before = curr->prev;
			dNode* next = curr->next;
			dNode* after = curr->next->next;
			// check if pos is head.
			if (curr == head)
			{
				head = curr->next;
			}
			// check if list has only two nodes.
			if (before != next)
			{
				before->next = next;
				next->prev = before;
				next->next = curr;
				curr->prev = next;
				curr->next = after;
				after->prev = curr;
			}
			*list = head;
			return 0;
		}
		++tempPos;
		*list = curr->next;
	} while (*list != head);
	return -1; // pos not in list, reset list.
}

int cdList::movePtrDown(dNode** list, dNode* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	dNode* head = *list;
	if (ptr == head->prev) return 0;

	dNode* curr = nullptr;
	do {
		curr = *list;
		if (curr == ptr)
		{
			dNode* before = curr->prev;
			dNode* newPos = curr->next;
			dNode* after = curr->next->next;
			before->next = newPos;
			newPos->prev = before;
			newPos->next = curr;
			curr->prev = newPos;
			curr->next = after;
			after->prev = curr;
			if (curr == head)
			{
				head = newPos;
			}
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
	return -1;
}

int cdList::clear(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* head = *list;
	do {
		dNode* dummy = *list;
		if (dummy->next != head)
		{
			*list = dummy->next;
			delete dummy;
		}
		else if (dummy->next == head)
		{
			delete dummy;
			*list = nullptr;
			return 0;
		}
	} while (*list != nullptr);
}

int cdList::isEmpty(dNode* list)
{
	if (list == nullptr) return 1;
	else return 0;
}

int cdList::size(dNode* list, int &nodeCount)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != head);
	return 0;
}

int cdList::print(dNode* list)
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

int cdList::printReverse(dNode* list)
{
	if (list == nullptr) return 1;

	dNode* head = list;
	int tempPos;
	this->size(list, tempPos);
	std::cout << "#\tdata:\tcurr:\t\t\tnext:\t\t\tprev:\n";
	do {
		list = list->prev;
		--tempPos;
		std::cout << tempPos << '\t' << list->data << '\t' << list << '\t' << list->next << '\t' << list->prev << '\n';
	} while (list != head);
	std::cout << '\n';
	return 0;
}

int cdList::reverse(dNode** list)
{
	if (*list == nullptr) return 1;

	dNode* tail = *list;
	dNode* head = *list;
	*list = tail->next;

	dNode* curr = nullptr;
	do {
		curr = *list;
		dNode* temp = curr->next;
		curr->next = head;
		curr->prev = tail;
		head->prev = curr;
		tail->next = curr;
		head = curr;
		*list = temp;
	} while (*list != tail);
	*list = head;
	return 0;
}

int cdList::swap(dNode** list, dNode* ptr1, dNode* ptr2)
{
	if (*list == nullptr) return 1; // list is empty.
	if (ptr1 == nullptr or ptr2 == nullptr) return 2;
	if (ptr1 == ptr2) return 4;

	dNode* head = *list;
	dNode* tail = head->prev;
	// check if list has only one node.
	if (head->next == head) return 5;
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
	} while (*list != head);
	// swap ptr1 and ptr2.
	if (foundPtr1 == true and foundPtr2 == true)
	{
		dNode* before1 = ptr1->prev;
		dNode* after1 = ptr1->next;
		dNode* before2 = ptr2->prev;
		dNode* after2 = ptr2->next;
		// check if ptr1 or ptr2 is head.
		if (ptr1 == head)
		{
			head = ptr2;
		}
		else if (ptr2 == head)
		{
			head = ptr1;
		}
		// check if ptr1 or pt2 is tail.
		if (ptr1 == tail)
		{
			after1 = head;
		}
		else if (ptr2 == tail)
		{
			after2 = head;
		}
		// check if ptr1 and ptr2 are adjacent.
		if (ptr1->next == ptr2)
		{
			before1->next = ptr2;
			ptr2->prev = before1;
			ptr2->next = ptr1;
			ptr1->prev = ptr2;
			ptr1->next = after2;
			after2->prev = ptr1;
		}
		else if (ptr2->next == ptr1)
		{
			before2->next = ptr1;
			ptr1->prev = before2;
			ptr1->next = ptr2;
			ptr2->prev = ptr1;
			ptr2->next = after1;
			after1->prev = ptr2;
		}
		else
		{
			before1->next = ptr2;
			ptr2->prev = before1;
			ptr2->next = after1;
			after1->prev = ptr2;

			before2->next = ptr1;
			ptr1->prev = before2;
			ptr1->next = after2;
			after2->prev = ptr1;
		}
		*list = head;
		return 0;
	}
	else // ptr1 and/or ptr2 not in list.
	{
		*list = head;
		return -1;
	}
}

int cdList::shuffle(dNode** list)
{
	if (*list == nullptr) return 1; // list is empty.

	dNode* head = *list;
	// check if list has only one node.
	if (head->next == head) return 5;

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

int cdList::bubbleSort(dNode** list, bool isAscending, int &swapCount, int &sweepCount)
{
	if (*list == nullptr) return 1; // list is empty.
	// check if list has only one node.
	dNode* head = *list;
	if (head->next == head) return 5;
	// define and initialize varaibles.
	dNode* before = nullptr; // node before adjacent nodes under test.
	dNode* curr = nullptr; // first adjacent node under test.
	dNode* test = nullptr; // second adjacent node under test.
	dNode* after = nullptr; // node after adjacent nodes under test.
	int swaps = 0; // node swaps per sweep.
	swapCount = 0; // total node swaps.
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
					}
					before->next = test;
					test->prev = before;
					test->next = curr;
					curr->prev = test;
					curr->next = after;
					after->prev = curr;
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
					}
					before->next = test;
					test->prev = before;
					test->next = curr;
					curr->prev = test;
					curr->next = after;
					after->prev = curr;
					*list = curr;
					++swaps;
				}
				else
				{
					*list = curr->next;
				}
			}
		} while (after != head);
		swapCount += swaps;
		++sweepCount;
		*list = head; // reset list.
	} while (swaps != 0);

	return 0;
}