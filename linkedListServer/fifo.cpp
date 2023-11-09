#include "fifo.h"
// sweeney's hand-rolled first-in-first-out (FIFO) class.

// error codes:
// 0: no error.
// 1: fifo full.
// 2: fifo almost full.
// 3: fifo almost empty.
// 4: fifo empty.
// 5: underflow.
// 6: overflow.
// 7: fifo not configured.

int fifo::config(int depth)
{
	if (depth > 0 and depth <= 4096)
	{
		fifoConfig = true;
		depthCount = depth;
		std::cout << "FIFO depth: " << depthCount << "\n\n";
		return 0;
	}
	else return 7; // fifo not configured.
}

int fifo::wr_en(node* &list, int din)
{
	if (fifoConfig == false) return 7; // fifo not configured.

	int wordCount;
	int result = this->data_count(list, wordCount);
	if (wordCount == depthCount) return 6; // full, overflow.

	if (list == nullptr)
	{
		node* newNode = new node();
		newNode->data = din;
		list = newNode;
		return 0;
	}

	node* head = list;
	do {
		if (list->next == nullptr)
		{
			node* newNode = new node();
			newNode->data = din;
			list->next = newNode;
			list = head;
			return 0;
		}
		list = list->next;
	} while (list != nullptr);
}

int fifo::rd_en(node** list, int &dout)
{
	if (fifoConfig == false) return 7; // fifo not configured.

	if (*list == nullptr) return 5; // empty, underflow.

	node* head = *list;
	dout = head->data;
	if (head->next == nullptr)
	{
		delete head;
		*list = nullptr;
		return 0;
	}
	else
	{
		*list = head->next;
		delete head;
		return 0;
	}
}

int fifo::data_count(node* list, int &wordCount)
{
	if (fifoConfig == false) return 7; // fifo not configured.

	wordCount = 0;
	if (list == nullptr) return 4; // empty.

	do {
		++wordCount;
		list = list->next;
	} while (list != nullptr);

	if (wordCount == 1) return 3; // almost empty.
	else if (wordCount == depthCount - 1) return 2; // almost full.
	else if (wordCount == depthCount) return 1; // full.
	else return 0;
}

int fifo::rst(node** list)
{
	if (fifoConfig == false) return 7; // fifo not configured.

	if (*list == nullptr) return 4; // empty.

	do {
		node* dummy = *list;
		*list = dummy->next;
		delete dummy;
	} while (*list != nullptr);
	return 0;
}

int fifo::print(node* list)
{
	if (fifoConfig == false) return 7; // fifo not configured.

	if (list == nullptr) return 4; // empty.

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