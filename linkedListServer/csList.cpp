#include "csList.h"
#include "random.h" // required for shuffle function.
// sweeney's hand-rolled circular singly linked list.
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

node* csList::init(int data)
{
	node* newNode = new node();
	newNode->data = data;
	newNode->next = newNode;
	return newNode;
}

int csList::addNodeFront(node** list, int data)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	// find tail node.
	do {
		node* curr = *list;
		if (curr->next == head) // found tail.
		{
			node* newNode = new node();
			newNode->data = data;
			newNode->next = head;
			head = newNode;
			curr->next = head;
			*list = head;
			return 0;
		}
		*list = curr->next;
	} while (*list != head);
}

int csList::addNodeBack(node* list, int data)
{
	if (list == nullptr) return 1;

	node* head = list;
	do {
		if (list->next == head)
		{
			node* newNode = new node();
			newNode->data = data;
			newNode->next = head;
			list->next = newNode;
			return 0;
		}
		list = list->next;
	} while (list != head);
}

int csList::addNodeByPos(node** list, int pos, int data)
{
	if (*list == nullptr) return 1; // list is empty.

	node* head = *list;
	// find pos in list.
	if (pos == 0) // pos is head node.
	{
		node* newNode = new node();
		newNode->data = data;
		newNode->next = head;
		// find tail node.
		node* tail = nullptr;
		this->findTailReturnPtr(*list, tail);
		tail->next = newNode;
		*list = newNode; // reset list.
		return 0;
	}
	else
	{
		*list = head->next; // skip head node.
		node* prev = head; // store previous node in sweep.
		int tempPos = 1;
		do {
			node* curr = *list;
			if (tempPos == pos)
			{
				node* newNode = new node();
				newNode->data = data;
				prev->next = newNode;
				newNode->next = curr;
				*list = head; // reset list.
				return 0;
			}
			++tempPos;
			prev = curr;
			*list = curr->next;
		} while (*list != head);
		*list = head; // pos not in list, reset list.
		return -1;
	}
}

int csList::deleteNodeFront(node** list)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	if (head->next == head) // check if list has only one node.
	{
		delete head;
		*list = nullptr;
		return 0;
	}

	do {
		node* dummy = *list;
		if (dummy->next == head)
		{
			node* newHead = head->next;
			dummy->next = newHead;
			delete head;
			*list = newHead;
			return 0;
		}
		*list = dummy->next;
	} while (*list != head);
}

int csList::deleteNodeBack(node** list)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	if (head->next == head) // check if list has only one node.
	{
		delete head;
		*list = nullptr;
		return 0;
	}

	do {
		node* dummy = *list;
		if (dummy->next->next == head)
		{
			delete dummy->next;
			dummy->next = head;
			*list = head;
			return 0;
		}
		*list = dummy->next;
	} while (*list != head);
}

int csList::deleteNodeByPos(node** list, int pos)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	if (pos == 0) // delete node in first position.
	{
		if (head->next == head) // check if list has only one node.
		{
			delete head;
			*list = nullptr;
			return 0;
		}
		else
		{
			do {
				node* dummy = *list;
				if (dummy->next == head)
				{
					dummy->next = head->next;
					*list = head->next;
					delete head;
					return 0;
				}
				*list = dummy->next;
			} while (*list != head);
		}
	}
	else
	{
		int tempPos = 0;
		do {
			node* curr = *list;
			node* dummy = curr->next;
			if (tempPos == pos - 1)
			{
				curr->next = dummy->next;
				delete dummy;
				*list = head;
				return 0;
			}
			++tempPos;
			*list = curr->next;
		} while (*list != head);
		return -1;
	}
}

int csList::deleteNodeByPtr(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;
	if (ptr == head) // delete node in first position.
	{
		if (head->next == head) // check if list has only one node.
		{
			delete head;
			*list = nullptr;
			return 0;
		}
		else
		{
			do {
				node* dummy = *list;
				if (dummy->next == head)
				{
					dummy->next = head->next;
					*list = head->next;
					delete head;
					return 0;
				}
				*list = dummy->next;
			} while (*list != head);
		}
	}
	else
	{
		do {
			node* curr = *list;
			node* dummy = curr->next;
			if (dummy == ptr)
			{
				curr->next = dummy->next;
				delete dummy;
				*list = head;
				return 0;
			}
			*list = dummy->next;
		} while (*list != head);
		return -1;
	}
}

int csList::deleteBeforePos(node** list, int pos)
{
	if (*list == nullptr) return 1;
	if (pos == 0) return 0; // invalid.
	node* head = *list;
	// pos == 0 is invalid, skip head.
	*list = head->next;
	node* prev = *list;
	int tempPos = 1;
	do {
		node* curr = *list;
		if (tempPos == pos)
		{
			// detach list before pos.
			prev->next = head;
			// delete detached list.
			node* temp = head;
			do {
				node* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != head);
			// assign new head.
			node* newHead = curr;
			// find tail, connect to new head.
			do {
				curr = *list;
				if (curr->next == head) // found tail.
				{
					curr->next = newHead;
					*list = newHead;
					return 0;
				}
				*list = curr->next;
			} while (*list != head);
		}
		++tempPos;
		prev = curr;
		*list = curr->next;
	} while (*list != head);
	*list = head; // pos not in list, reset list.
	return -1;
}

int csList::deleteBeforePtr(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;
	if (ptr == head) // invalid.
	{
		*list = head;
		return 0;
	}
	node* prev = *list; // store previous node in sweep.
	*list = head->next; // ptr == 0 is invalid, skip head.
	// find ptr in list.
	do {
		node* curr = *list;
		if (curr == ptr) // ptr found.
		{
			prev->next = nullptr; // detach list before ptr.
			// delete detached list.
			node* temp = head;
			do {
				node* dummy = temp;
				temp = temp->next;
				delete dummy;
			} while (temp != nullptr);
			node* newHead = curr; // assign new head node.
			// find tail node.
			do {
				curr = *list;
				if (curr->next == head)
				{
					// connect tail to new head.
					curr->next = newHead;
					*list = newHead;
					return 0;
				}
				*list = curr->next;
			} while (*list != head);
		}
		*list = curr->next;
	} while (*list != head);
	*list = head; // ptr not found in list, reset list.
	return -1;
}

int csList::deleteAfterPos(node** list, int pos)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	int tempPos = 0;
	do {
		node* curr = *list;
		if (tempPos == pos) // found pos in list.
		{
			// check if node is tail.
			if (curr->next == nullptr)
			{
				*list = head;
				return 0;
			}
			// else, detach list after pos.
			node* temp = curr->next;
			// connect new tail to head.
			curr->next = head;
			// delete detached list.
			do {
				node* dummy = temp;
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

int csList::deleteAfterPtr(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;
	do {
		node* curr = *list;
		if (curr == ptr) // found ptr in list.
		{
			// check if ptr is tail.
			if (curr->next == nullptr)
			{
				*list = head;
				return 0;
			}
			// detach list after ptr.
			node* temp = curr->next;
			curr->next = head;
			// delete detached list.
			do {
				node* dummy = temp;
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

int csList::returnPtrByPos(node* list, int pos, node* &ptr)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::returnPosByPtr(node* list, int &pos, node* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = list;
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

int csList::returnDataByPos(node* list, int &data, int pos)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::returnDataByPtr(node* list, int &data, node* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = list;
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

int csList::updateDataByPos(node* list, int pos, int data)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::updateDataByPtr(node* list, int data, node* ptr)
{
	if (list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = list;
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

int csList::findDataReturnPos(node* list, int data, int &pos)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::findDataReturnPtr(node* list, int data, node* &ptr)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::findMinReturnPos(node* list, int &min, int &pos)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::findMinReturnPtr(node* list, int &min, node* &ptr)
{
	if (list == nullptr) return 1;

	node* head = list;
	min = head->data;
	ptr = head;
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

int csList::findMaxReturnPos(node* list, int &max, int &pos)
{
	if (list == nullptr) return 1;

	node* head = list;
	max = list->data;
	pos = 0;

	list = list->next;
	int tempPos = 1;
	do {
		if (list->data > max)
		{
			max = list->data;
			pos = tempPos;
		}
		++tempPos;
		list = list->next;
	} while (list != head);
	return 0;
}

int csList::findMaxReturnPtr(node* list, int &max, node* &ptr)
{
	if (list == nullptr) return 1;

	node* head = list;
	max = head->data;
	ptr = head;
	list = list->next;
	do {
		if (list->data > max)
		{
			max = list->data;
			ptr = list;
		}
		list = list->next;
	} while (list != head);
	return 0;
}

int csList::findTailReturnPos(node* list, int &pos)
{
	if (list == nullptr) return 1;

	node* head = list;
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

int csList::findTailReturnPtr(node* list, node* &ptr)
{
	if (list == nullptr) return 1;

	node* head = list;
	do {
		if (list->next == head)
		{
			ptr = list;
			return 0;
		}
		list = list->next;
	} while (list != head);
}

int csList::movePosToFront(node** list, int pos)
{
	if (*list == nullptr) return 1;
	if (pos == 0) return -2; // no action needed.

	node* head = *list;
	node* prev = *list; // node previous to pos.
	node* temp = *list; // hold 'prev' node b/w sweeps.
	node* posNode = *list; // node in pos.
	node* tail = *list;
	// check if list has only one node.
	if (head->next == head)
	{
		return 5;
	}
	*list = head->next;
	// find pos in list.
	bool foundPos = false;
	int tempPos = 1;
	do {
		node* curr = *list;
		if (tempPos == pos) // found pos.
		{
			foundPos = true;
			posNode = curr;
			prev = temp;
		}
		if (curr->next == head) // find tail.
		{
			tail = curr;
		}
		++tempPos;
		temp = curr;
		*list = curr->next;
	} while (*list != head);

	if (foundPos == true)
	{
		tail->next = posNode;
		prev->next = posNode->next;
		posNode->next = head;
		head = posNode;
		*list = head;
		return 0;
	}
	else
	{
		*list = head; // pos not in list.
		return -1;
	}
}

int csList::movePtrToFront(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;
	if (ptr == head) return 0;

	bool foundPtr = false;
	node* curr = nullptr;
	do {
		curr = *list;
		if (curr->next == ptr)
		{
			foundPtr = true;
			curr->next = ptr->next;
		}
		*list = curr->next;
	} while (curr->next != head);

	if (foundPtr == true)
	{
		curr->next = ptr;
		ptr->next = head;
		head = ptr;
		*list = head;
		return 0;
	}
	else return -1; // ptr not in list.
}

int csList::movePosToBack(node** list, int pos)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	// check if list has only one node.
	if (head->next == head)
	{
		return 5;
	}
	node* prev = *list; // node previous to pos.
	node* temp = *list; // hold 'prev' node b/w sweeps.
	node* posNode = *list; // node in pos.
	node* tail = *list;
	// find pos in list.
	bool foundPos = false;
	int tempPos = 0;
	do {
		node* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail.
			if (curr->next == head)
			{
				*list = head; // no action needed.
				return -2;
			}
			foundPos = true;
			posNode = curr;
			prev = temp;
		}
		if (curr->next == head) // find tail.
		{
			tail = curr;
		}
		++tempPos;
		temp = curr;
		*list = curr->next;
	} while (*list != head);

	if (foundPos == true)
	{
		if (posNode == head)
		{
			head = head->next;
			tail->next = posNode;
			posNode->next = head;
		}
		else
		{
			prev->next = posNode->next;
			tail->next = posNode;
			posNode->next = head;
		}
		*list = head;
		return 0;
	}
	else
	{
		*list = head;
		return -1;
	}
}

int csList::movePtrToBack(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;

	node* tempPrev = *list; // prev node in sweep.
	node* prev = *list; // store ptr prev node.
	node* tail = nullptr; // tail node.
	bool foundPtr = false;
	// find ptr in list.
	do {
		node* curr = *list;
		if (curr == ptr) // ptr found.
		{
			// check if ptr is tail node.
			if (curr->next == head)
			{
				*list = head;
				return 0;
			}
			foundPtr = true;
			prev = tempPrev;
		}
		// find tail node.
		if (curr->next == head)
		{
			tail = curr;
		}
		tempPrev = curr;
		*list = curr->next;
	} while (*list != head);

	if (foundPtr == true)
	{
		if (ptr == head)
		{
			head = head->next;
		}
		else
		{
			prev->next = ptr->next;
		}
		tail->next = ptr;
		ptr->next = head;
		*list = head;
		return 0;
	}
	else // ptr not in list, reset list.
	{
		*list = head;
		return -1;
	}
}

int csList::movePosUp(node** list, int pos)
{
	if (*list == nullptr) return 1;
	if (pos == 0) return 0; // no action needed.

	node* head = *list;
	node* tail = *list;
	node* before = *list; // node before nodes to be swapped.
	node* prev = *list; // node previous to pos.
	node* posNode = *list; // node in pos.
	node* temp1 = *list; // hold 'before' node b/w sweeps.
	node* temp2 = *list; // hold 'prev' node b/w sweeps.
	// check if list has only only node.
	if (head->next == head)
	{
		return 0; // no action needed
	}
	*list = head->next;
	// find pos in list.
	bool foundPos = false;
	int tempPos = 1;
	do {
		node* curr = *list;
		if (tempPos == pos) // found pos.
		{
			foundPos = true;
			before = temp2;
			prev = temp1;
			posNode = curr;
		}
		if (curr->next == head) // find tail.
		{
			tail = curr;
		}
		++tempPos;
		temp2 = temp1;
		temp1 = curr;
		*list = curr->next;
	} while (*list != head);

	if (foundPos == true)
	{
		if (prev == head)
		{
			tail->next = posNode;
			head = posNode;
		}
		else
		{
			before->next = posNode;
		}
		prev->next = posNode->next;
		posNode->next = prev;
		*list = head;
		return 0;
	}
	else // pos not in list, resest list.
	{
		*list = head;
		return -1;
	}
}

int csList::movePtrUp(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;
	node* before = *list; // node before nodes to be swapped.
	node* prev = *list; // node previous to ptr.
	node* tail = *list;
	node* temp1 = *list; // hold 'before' node b/w sweeps.
	node* temp2 = *list; // hold 'prev' node b/w sweeps.
	bool foundPtr = false;
	// find ptr in list.
	do {
		node* curr = *list;
		if (curr == ptr) // found ptr.
		{
			foundPtr = true;
			before = temp2;
			prev = temp1;
		}
		if (curr->next == head) // find tail node.
		{
			tail = curr;
		}
		temp2 = temp1; // 'before'.
		temp1 = curr; // 'prev'.
		*list = curr->next;
	} while (*list != head);

	if (foundPtr == true)
	{
		node* temp = ptr->next;
		if (prev == head)
		{
			tail->next = ptr;
			ptr->next = prev;
			prev->next = temp;
			head = ptr;
		}
		else
		{
			before->next = ptr;
			ptr->next = prev;
			prev->next = temp;
		}
		*list = head;
		return 0;
	}
	else // ptr not in list, reset list.
	{
		*list = head;
		return -1;
	}
}

int csList::movePosDown(node** list, int pos)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	node* tail = *list;
	node* prev = *list; // node previous to pos.
	node* posNode = *list; // node in pos.
	node* temp = *list; // hold 'prev' node b/w sweeps.
	// find pos in list.
	bool foundPos = false;
	int tempPos = 0;
	do {
		node* curr = *list;
		if (tempPos == pos)
		{
			// check if pos is tail.
			if (curr->next == head) // no action needed.
			{
				*list = head;
				return 0;
			}
			foundPos = true;
			prev = temp;
			posNode = curr;
		}
		if (curr->next == head) // find tail.
		{
			tail = curr;
		}
		++tempPos;
		temp = curr;
		*list = curr->next;
	} while (*list != head);

	if (foundPos == true)
	{
		node* next = posNode->next;
		if (posNode == head)
		{
			tail->next = next;
			head = next;
		}
		else
		{
			prev->next = next;
		}
		posNode->next = next->next;
		next->next = posNode;
		*list = head;
		return 0;
	}
	else // pos not in list, reset list.
	{
		*list = head;
		return -1;
	}
}

int csList::movePtrDown(node** list, node* ptr)
{
	if (*list == nullptr) return 1;
	if (ptr == nullptr) return 2;

	node* head = *list;
	node* prev = *list; // node before ptr.
	node* after = *list; // node after nodes to be swapped.
	node* tail = *list;
	node* temp = *list; // hold 'prev' node b/w sweeps.
	bool foundPtr = false;

	// find ptr in list.
	do {
		node* curr = *list;
		if (curr == ptr) // found ptr.
		{
			// if ptr is tail, no action needed.
			if (curr->next == head)
			{
				*list = head;
				return 0;
			}
			else
			{
				foundPtr = true;
				prev = temp;
				after = curr->next->next;
			}
		}
		if (curr->next == head) // find tail.
		{
			tail = curr;
		}
		temp = curr; // 'prev'.
		*list = curr->next;
	} while (*list != head);

	if (foundPtr == true)
	{
		node* temp = ptr->next;
		if (ptr == head)
		{
			tail->next = temp;
			temp->next = ptr;
			ptr->next = after;
			head = temp;
		}
		else
		{
			prev->next = temp;
			temp->next = ptr;
			ptr->next = after;
		}
		*list = head;
		return 0;
	}
	else // ptr not in list.
	{
		*list = head;
		return -1;
	}
}

int csList::clear(node** list)
{
	if (*list == nullptr) return 1;

	node* head = *list;
	do {
		node* dummy = *list;
		if (dummy->next == head)
		{
			delete dummy;
			*list = nullptr;
			return 0;
		}
		*list = dummy->next;
		delete dummy;
	} while (*list != nullptr);
	return 0;
}

int csList::size(node* list, int &nodeCount)
{
	if (list == nullptr) return 1;

	node* head = list;
	nodeCount = 0;
	do {
		++nodeCount;
		list = list->next;
	} while (list != head);
	return 0;
}

int csList::isEmpty(node* list)
{
	if (list == nullptr) return 1;
	else return 0;
}

int csList::print(node* list)
{
	if (list == nullptr) return 1;

	node* head = list;
	int tempPos = 0;
	std::cout << "#\tdata:\tcurr:\t\t\tnext:\n";
	do {
		std::cout << tempPos << '\t' << list->data << '\t' << list << '\t' << list->next << '\n';
		++tempPos;
		list = list->next;
	} while (list != head);
	std::cout << '\n';
	return 0;
}

int csList::reverse(node** list)
{
	if (*list == nullptr) return 1;

	node* tail = *list;
	node* head = tail;

	*list = head->next;
	do {
		node* curr = *list;
		node* temp = curr->next;
		curr->next = head;
		head = curr;
		tail->next = head;
		*list = temp;
	} while (*list != tail);
	*list = head;
	return 0;
}

int csList::swap(node** list, node* ptr1, node* ptr2)
{
	if (*list == nullptr) return 1; // list is empty.
	if (ptr1 == nullptr or ptr2 == nullptr) return 2;
	if (ptr1 == ptr2) return 4; // no action needed.

	node* head = *list;
	// check if list has only one node.
	if (head->next == head) return 5;
	// find ptr1 and ptr2 in list.
	bool foundPtr1 = false;
	bool foundPtr2 = false;
	node* before1 = *list; // node before ptr1 in list.
	node* before2 = *list; // node before ptr2 in list.
	node* temp = *list; // store previous node in list sweep.
	node* tail = *list;
	do {
		node* curr = *list;
		if (curr == ptr1) // found ptr1.
		{
			foundPtr1 = true;
			before1 = temp;
		}
		if (curr == ptr2) // found ptr2.
		{
			foundPtr2 = true;
			before2 = temp;
		}
		if (curr->next == head) // find tail.
		{
			tail = curr;
		}
		temp = curr;
		*list = curr->next;
	} while (*list != head);

	if (foundPtr1 == true and foundPtr2 == true)
	{
		node* after1 = ptr1->next; // node after ptr1 in list.
		node* after2 = ptr2->next; // node after ptr2 in list.
		// check if ptr1 or ptr2 is head.
		if (ptr1 == head)
		{
			before1 = tail;
			head = ptr2;
		}
		else if (ptr2 == head)
		{
			before2 = tail;
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
			ptr2->next = ptr1;
			ptr1->next = after2;
		}
		else if (ptr2->next == ptr1)
		{
			before2->next = ptr1;
			ptr1->next = ptr2;
			ptr2->next = after1;
		}
		else
		{
			before1->next = ptr2;
			ptr2->next = after1;
			before2->next = ptr1;
			ptr1->next = after2;
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

int csList::shuffle(node** list)
{
	if (*list == nullptr) return 1; // list is empty.

	node* head = *list;
	// check if list has only one node.
	if (head->next == head) return 5;

	random random;
	random.initMt();

	int nodeCount;
	int result = size(*list, nodeCount);
	int position1;
	int position2;
	int temp = 0;
	// swap random positions nodeCount^2 number of times.
	do {
		// get two unique list positions.
		do {
			position1 = random.getNum(0, nodeCount - 1);
			position2 = random.getNum(0, nodeCount - 1);
		} while (position1 == position2);
		// get pointers to list positions.
		node* ptr1 = nullptr;
		node* ptr2 = nullptr;
		this->returnPtrByPos(*list, position1, ptr1);
		this->returnPtrByPos(*list, position2, ptr2);
		swap(list, ptr1, ptr2);
		++temp;
	} while (temp < pow(nodeCount, 2));
	return 0;
}

int csList::bubbleSort(node** list, bool isAscending, int &swapCount, int &sweepCount)
{
	if (*list == nullptr) return 1; // list is empty.

	node* head = *list;
	// check if list has only one node.
	if (head->next == head) return 5;
	// delcare and initialze variables.
	node* prev = *list; // previous node in list sweep.
	node* tail = *list; // tail node.
	int swaps = 0; // store node swap count b/w sweeps.
	swapCount = 0;
	sweepCount = 0;
	// find tail node.
	do {
		node* curr = *list;
		if (curr->next == head)
		{
			tail = curr;
		}
		*list = curr->next;
	} while (*list != head);
	*list = head; // reset list.
	// sweep list, swapping nodes as needed.
	// stop on first sweep with no swaps.
	do {
		// compare adjacent nodes, swap according to isAscending.
		swaps = 0;
		do {
			node* curr = *list; // current node.
			node* test = curr->next; // node after current node.
			if (isAscending == true) // sort ascending.
			{
				if (curr->data > test->data)
				{
					node* temp = test->next;
					if (curr == head)
					{
						tail->next = test;
						head = test;
					}
					else if (test == tail)
					{
						prev->next = test;
						tail = curr;
					}
					else
					{
						prev->next = test;
					}
					test->next = curr;
					curr->next = temp;
					prev = test;
					*list = curr;
					++swaps;
				}
				else
				{
					prev = curr;
					*list = test;
				}
			}
			else // sort descending.
			{
				if (curr->data < test->data)
				{
					node* temp = test->next;
					if (curr == head)
					{
						tail->next = test;
						head = test;
					}
					else if (test == tail)
					{
						prev->next = test;
						tail = curr;
					}
					else
					{
						prev->next = test;
					}
					test->next = curr;
					curr->next = temp;
					prev = test;
					*list = curr;
					++swaps;
				}
				else
				{
					prev = curr;
					*list = test;
				}
			}
		} while (*list != tail);
		swapCount += swaps;
		++sweepCount;
		*list = head; // reset list.
		
	} while (swaps != 0);
	*list = head; // reset list.
	return 0;
}