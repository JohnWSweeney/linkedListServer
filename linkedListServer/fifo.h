#pragma once
#include "nodes.h"
// sweeney's hand-rolled first-in-first-out (FIFO) class.

class fifo
{
	// error codes:
	// 0: no error.
	// 1: fifo full.
	// 2: fifo almost full.
	// 3: fifo almost empty.
	// 4: fifo empty.
	// 5: underflow.
	// 6: overflow.
	// 7: fifo not configured.
private:
	bool fifoConfig = false;
	int depthCount;
public:
	int config(int count);
	int wr_en(node* &list, int din);
	int rd_en(node** list, int &dout);
	int data_count(node* list, int &wordCount);
	int rst(node** list);
	int print(node* list);
};