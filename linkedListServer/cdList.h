#pragma once
#include "nodes.h"
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

class cdList
{
public:
	dNode* init(int data);
	int addNodeFront(dNode** list, int data);
	int addNodeBack(dNode* list, int data);
	int addNodeByPos(dNode** list, int pos, int data);
	int deleteNodeFront(dNode** list);
	int deleteNodeBack(dNode** list);
	int deleteNodeByPos(dNode** list, int pos);
	int deleteNodeByPtr(dNode** list, dNode* ptr);
	int deleteBeforePos(dNode** list, int pos);
	int deleteBeforePtr(dNode** list, dNode* ptr);
	int deleteAfterPos(dNode** list, int pos);
	int deleteAfterPtr(dNode** list, dNode* ptr);
	int returnPtrByPos(dNode* list, int pos, dNode* &ptr);
	int returnPosByPtr(dNode* list, int &pos, dNode* ptr);
	int returnDataByPos(dNode* list, int &data, int pos);
	int returnDataByPtr(dNode* list, int &data, dNode* ptr);
	int updateDataByPos(dNode* list, int data, int pos);
	int updateDataByPtr(dNode* list, int data, dNode* ptr);
	int findDataReturnPos(dNode* list, int data, int &pos);
	int findDataReturnPtr(dNode* list, int data, dNode* &ptr);
	int findMinReturnPos(dNode* list, int &min, int &pos);
	int findMinReturnPtr(dNode* list, int &min, dNode* &ptr);
	int findMaxReturnPos(dNode* list, int &max, int &pos);
	int findMaxReturnPtr(dNode* list, int &max, dNode* &ptr);
	int findTailReturnPos(dNode* list, int &pos);
	int findTailReturnPtr(dNode* list, dNode* &ptr);
	int movePosToFront(dNode** list, int pos);
	int movePtrToFront(dNode** list, dNode* ptr);
	int movePosToBack(dNode** list, int pos);
	int movePtrToBack(dNode** list, dNode* ptr);
	int movePosUp(dNode** list, int pos);
	int movePtrUp(dNode** list, dNode* ptr);
	int movePosDown(dNode** list, int pos);
	int movePtrDown(dNode** list, dNode* ptr);
	int clear(dNode** list);
	int isEmpty(dNode* list);
	int size(dNode* list, int &nodeCount);
	int print(dNode* list);
	int printReverse(dNode* list);
	int reverse(dNode** list);
	int swap(dNode** list, dNode* ptr1, dNode* ptr2);
	int shuffle(dNode** list);
};