#include "demos.h"
#include "atomicBool.h"
#include "random.h"
#include "sList.h"
#include "dList.h"
#include "csList.h"
#include "cdList.h"
#include "stack.h"
#include "queue.h"
#include "deque.h"
#include "priorityQueue.h"
#include "fifo.h"

void sDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Singly linked list demo started.\n";
	sList slist;
	int result;
	int position;
	int data;
	int nodeCount;
	node* list = nullptr;
	node* ptr = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "init")
		{
			list = slist.init(cmd.input1);
			result = slist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				slist.print(list);
			}
		}
		else if (cmd.function == "addNodeFront")
		{
			result = slist.addNodeFront(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else
			{
				std::cout << "List is empty.\n\n";
			}
		}
		else if (cmd.function == "addNodeBack")
		{
			result = slist.addNodeBack(list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodeByPos")
		{
			result = slist.addNodeByPos(&list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPos")
		{
			result = slist.deleteNodeByPos(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteNodeFront")
		{
			result = slist.deleteNodeFront(&list);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeBack")
		{
			result = slist.deleteNodeBack(&list);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPtr")
		{
			result = slist.deleteNodeByPtr(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "deleteBeforePos")
		{
			result = slist.deleteBeforePos(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteBeforePtr")
		{
			result = slist.deleteBeforePtr(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "deleteAfterPos")
		{
			result = slist.deleteAfterPos(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteAfterPtr")
		{
			result = slist.deleteAfterPtr(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "returnPtrByPos")
		{
			result = slist.returnPtrByPos(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Pointer to position " << cmd.input1 << ": " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Requested postition is out of bounds.\n";
			}
		}
		else if (cmd.function == "returnPosByPtr")
		{
			result = slist.returnPosByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Pointer " << ptr << " is in position " << data << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "returnDataByPos")
		{
			result = slist.returnDataByPos(list, data, cmd.input1);
			if (result == 0)
			{
				std::cout << "Data in position " << cmd.input1 << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "returnDataByPtr")
		{
			result = slist.returnDataByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Data in pointer " << ptr << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "updateDataByPos")
		{
			result = slist.updateDataByPos(list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				slist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "updateDataByPtr")
		{
			result = slist.updateDataByPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				slist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "findDataReturnPos")
		{
			result = slist.findDataReturnPos(list, cmd.input1, data);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in position " << data << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "list is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findDataReturnPtr")
		{
			result = slist.findDataReturnPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in pointer " << ptr << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "list is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findMinReturnPos")
		{
			result = slist.findMinReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMinReturnPtr")
		{
			result = slist.findMinReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPos")
		{
			result = slist.findMaxReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPtr")
		{
			result = slist.findMaxReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPos")
		{
			result = slist.findTailReturnPos(list, position);
			if (result == 0)
			{
				std::cout << "Tail position: " << position << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPtr")
		{
			result = slist.findTailReturnPtr(list, ptr);
			if (result == 0)
			{
				std::cout << "Tail pointer: " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "movePosToFront")
		{
			result = slist.movePosToFront(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToFront")
		{
			result = slist.movePtrToFront(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosToBack")
		{
			result = slist.movePosToBack(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToBack")
		{
			result = slist.movePtrToBack(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosUp")
		{
			result = slist.movePosUp(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
		}
		else if (cmd.function == "movePtrUp")
		{
			result = slist.movePtrUp(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosDown")
		{
			result = slist.movePosDown(&list, cmd.input1);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
		}
		else if (cmd.function == "movePtrDown")
		{
			result = slist.movePtrDown(&list, ptr);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = slist.clear(&list);
			if (result == 0)
			{
				std::cout << "List cleared.\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = slist.isEmpty(list);
			if (result == 0)
			{
				std::cout << "List is not empty.\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = slist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}

		}
		else if (cmd.function == "print")
		{

			result = slist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				slist.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "reverse")
		{
			result = slist.reverse(&list);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodes")
		{
			for (int i = 0; i < 9; i++)
			{
				result = slist.addNodeBack(list, pow(i, 5));
				if (result == 1)
				{
					std::cout << "List is empty.\n";
					break;
				}
			}
			result = slist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				slist.print(list);
			}
		}
		else if (cmd.function == "addRandomNodes")
		{
			random random;
			random.initMt();
			for (int i = 0; i < cmd.input1; i++)
			{
				int num = random.getNum(cmd.input2, cmd.input3);
				result = slist.addNodeBack(list, num);
				if (result == 1)
				{
					std::cout << "List is empty.\n";
					break;
				}
			}
			result = slist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				slist.print(list);
			}
		}
		else if (cmd.function == "clearPtr")
		{
			ptr = nullptr;
			std::cout << "Pointer cleared.\n";
		}
		else if (cmd.function == "swap")
		{
			node* ptr1 = nullptr;
			node* ptr2 = nullptr;
			// get ptr1 from position 1.
			result = slist.returnPtrByPos(list, cmd.input1, ptr1);
			if (result == 0)
			{
				// get ptr2 from position 2.
				result = slist.returnPtrByPos(list, cmd.input2, ptr2);
				if (result == -1)
				{
					std::cout << "Postition 2 is not in list.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition 1 is not in list.\n";
			}
			// swap ptr1 and ptr2.
			result = slist.swap(&list, ptr1, ptr2);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 4)
			{
				 
			}
		}
		else if (cmd.function == "shuffle")
		{
			result = slist.shuffle(&list);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		else if (cmd.function == "bubbleSort")
		{
			result = slist.bubbleSort(&list, cmd.isAscending);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "selectionSort")
		{
			result = slist.selectionSort(&list, cmd.isAscending);
			if (result == 0)
			{
				result = slist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					slist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Singly linked list demo stopped.\n";
}

void dDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Doubly linked list demo started.\n";
	dList dlist;
	int result;
	int position;
	int data;
	int nodeCount;
	int swapCount;
	int sweepCount;
	dNode* list = nullptr;
	dNode* ptr = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "init")
		{
			list = dlist.init(cmd.input1);
			dlist.print(list);
		}
		else if (cmd.function == "addNodeFront")
		{
			result = dlist.addNodeFront(&list, cmd.input1);
			if (result == 0)
			{
				dlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodeBack")
		{
			result = dlist.addNodeBack(list, cmd.input1);
			if (result == 0)
			{
				dlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodeByPos")
		{
			result = dlist.addNodeByPos(&list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				dlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
		}
		else if (cmd.function == "deleteNodeFront")
		{
			result = dlist.deleteNodeFront(&list);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeBack")
		{
			result = dlist.deleteNodeBack(&list);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPos")
		{
			result = dlist.deleteNodeByPos(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is out of bounds.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPtr")
		{
			result = dlist.deleteNodeByPtr(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					dlist.size(list, nodeCount);
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else if (result == 1)
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "deleteBeforePos")
		{
			result = dlist.deleteBeforePos(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteBeforePtr")
		{
			result = dlist.deleteBeforePtr(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "deleteAfterPos")
		{
			result = dlist.deleteAfterPos(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteAfterPtr")
		{
			result = dlist.deleteAfterPtr(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "returnPtrByPos")
		{
			result = dlist.returnPtrByPos(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Pointer to position " << cmd.input1 << ": " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is out of bounds.\n";
			}
		}
		else if (cmd.function == "returnPosByPtr")
		{
			result = dlist.returnPosByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Pointer " << ptr << " is in position " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "returnFrontData")
		{
			result = dlist.returnFrontData(list, data);
			if (result == 0)
			{
				std::cout << "Data: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "returnBackData")
		{
			result = dlist.returnBackData(list, data);
			if (result == 0)
			{
				std::cout << "Data: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "returnDataByPos")
		{
			result = dlist.returnDataByPos(list, data, cmd.input1);
			if (result == 0)
			{
				std::cout << "Position " << cmd.input1 << " data: " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is out of bounds.\n";
			}
		}
		else if (cmd.function == "returnDataByPtr")
		{
			result = dlist.returnDataByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Data in pointer " << ptr << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "updateDataByPos")
		{
			result = dlist.updateDataByPos(list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is out of bounds.\n";
			}
		}
		else if (cmd.function == "updateDataByPtr")
		{
			result = dlist.updateDataByPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "findDataReturnPos")
		{
			result = dlist.findDataReturnPos(list, cmd.input1, data);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in position " << data << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findDataReturnPtr")
		{
			result = dlist.findDataReturnPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in pointer " << ptr << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findMinReturnPos")
		{
			result = dlist.findMinReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMinReturnPtr")
		{
			result = dlist.findMinReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPos")
		{
			result = dlist.findMaxReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPtr")
		{
			result = dlist.findMaxReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPos")
		{
			result = dlist.findTailReturnPos(list, position);
			if (result == 0)
			{
				std::cout << "Tail position: " << position << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPtr")
		{
			result = dlist.findTailReturnPtr(list, ptr);
			if (result == 0)
			{
				std::cout << "Tail pointer: " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "movePosToFront")
		{
			result = dlist.movePosToFront(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToFront")
		{
			result = dlist.movePtrToFront(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosToBack")
		{
			result = dlist.movePosToBack(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToBack")
		{
			result = dlist.movePtrToBack(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosUp")
		{
			result = dlist.movePosUp(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrUp")
		{
			result = dlist.movePtrUp(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosDown")
		{
			result = dlist.movePosDown(&list, cmd.input1);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrDown")
		{
			result = dlist.movePtrDown(&list, ptr);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = dlist.clear(&list);
			if (result == 0)
			{
				std::cout << "List cleared.\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = dlist.isEmpty(list);
			if (result == 0)
			{
				std::cout << "List is not empty.\n";
			}
			else if (result == 1)
			{
				std::cout << "list is empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = dlist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = dlist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "reverse")
		{
			result = dlist.reverse(&list);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodes")
		{
			if (list != NULL)
			{
				for (int i = 0; i < 9; i++)
				{
					dlist.addNodeBack(list, pow(i, 5));
				}
				dlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addRandomNodes")
		{
			random random;
			random.initMt();
			for (int i = 0; i < cmd.input1; i++)
			{
				int num = random.getNum(cmd.input2, cmd.input3);
				result = dlist.addNodeBack(list, num);
				if (result == 1)
				{
					std::cout << "List is empty.\n";
					break;
				}
			}
			result = dlist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				dlist.print(list);
			}
		}
		else if (cmd.function == "clearPtr")
		{
			ptr = nullptr;
			std::cout << "Pointer cleared.\n";
		}
		else if (cmd.function == "swap")
		{
			dNode* ptr1 = nullptr;
			dNode* ptr2 = nullptr;
			// get ptr1 from position 1.
			result = dlist.returnPtrByPos(list, cmd.input1, ptr1);
			if (result == 0)
			{
				// get ptr2 from position 2.
				result = dlist.returnPtrByPos(list, cmd.input2, ptr2);
				if (result == -1)
				{
					std::cout << "Postition 2 is not in list.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition 1 is not in list.\n";
			}

			// swap ptr1 and ptr2.
			result = dlist.swap(&list, ptr1, ptr2);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 4)
			{
				// 
			}
		}
		else if (cmd.function == "shuffle")
		{
			result = dlist.shuffle(&list);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		else if (cmd.function == "bubbleSort")
		{
			result = dlist.bubbleSort(&list, cmd.isAscending, swapCount, sweepCount);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "swapCount: " << swapCount << '\n';
					std::cout << "sweepCount: " << sweepCount << '\n';
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		else if (cmd.function == "selectionSort")
		{
			result = dlist.selectionSort(&list, cmd.isAscending);
			if (result == 0)
			{
				result = dlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Doubly linked list demo stopped.\n";
}

void csDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Circular singly linked list demo started.\n";
	csList cslist;
	int result;
	int position;
	int data;
	int nodeCount;
	int swapCount;
	int sweepCount;
	node* list = nullptr;
	node* ptr = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "init")
		{
			list = cslist.init(cmd.input1);
			cslist.print(list);
		}
		else if (cmd.function == "addNodeFront")
		{
			result = cslist.addNodeFront(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else
			{
				std::cout << "List is empty.\n\n";
			}
		}
		else if (cmd.function == "addNodeBack")
		{
			result = cslist.addNodeBack(list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodeByPos")
		{
			result = cslist.addNodeByPos(&list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				cslist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				cslist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition is not in list.\n";
			}
		}
		else if (cmd.function == "deleteNodeFront")
		{
			result = cslist.deleteNodeFront(&list);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeBack")
		{
			result = cslist.deleteNodeBack(&list);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPos")
		{
			result = cslist.deleteNodeByPos(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPtr")
		{
			result = cslist.deleteNodeByPtr(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "deleteBeforePos")
		{
			result = cslist.deleteBeforePos(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteBeforePtr")
		{
			result = cslist.deleteBeforePtr(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "deleteAfterPos")
		{
			result = cslist.deleteAfterPos(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteAfterPtr")
		{
			result = cslist.deleteAfterPtr(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "returnDataByPos")
		{
			result = cslist.returnDataByPos(list, data, cmd.input1);
			if (result == 0)
			{
				std::cout << "Data in position " << cmd.input1 << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "returnPtrByPos")
		{
			result = cslist.returnPtrByPos(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Pointer to position " << cmd.input1 << ": " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "returnPosByPtr")
		{
			result = cslist.returnPosByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Pointer " << ptr << " is in position " << data << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "returnDataByPos")
		{
			result = cslist.returnDataByPos(list, data, cmd.input1);
			if (result == 0)
			{
				std::cout << "Data in position " << cmd.input1 << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "returnDataByPtr")
		{
			result = cslist.returnDataByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Data in pointer " << ptr << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "updateDataByPos")
		{
			result = cslist.updateDataByPos(list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				cslist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "updateDataByPtr")
		{
			result = cslist.updateDataByPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				cslist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "findDataReturnPos")
		{
			result = cslist.findDataReturnPos(list, cmd.input1, position);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in position " << position << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findDataReturnPtr")
		{
			result = cslist.findDataReturnPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in pointer " << ptr << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "list is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findMinReturnPos")
		{
			result = cslist.findMinReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMinReturnPtr")
		{
			result = cslist.findMinReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPos")
		{
			result = cslist.findMaxReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPtr")
		{
			result = cslist.findMaxReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPos")
		{
			result = cslist.findTailReturnPos(list, position);
			if (result == 0)
			{
				std::cout << "Tail position: " << position << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPtr")
		{
			result = cslist.findTailReturnPtr(list, ptr);
			if (result == 0)
			{
				std::cout << "Tail pointer: " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "movePosToFront")
		{
			result = cslist.movePosToFront(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToFront")
		{
			result = cslist.movePtrToFront(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosToBack")
		{
			result = cslist.movePosToBack(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToBack")
		{
			result = cslist.movePtrToBack(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosUp")
		{
			result = cslist.movePosUp(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
		}
		else if (cmd.function == "movePtrUp")
		{
			result = cslist.movePtrUp(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosDown")
		{
			result = cslist.movePosDown(&list, cmd.input1);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
		}
		else if (cmd.function == "movePtrDown")
		{
			result = cslist.movePtrDown(&list, ptr);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = cslist.clear(&list);
			if (result == 0)
			{
				std::cout << "List cleared.\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = cslist.isEmpty(list);
			if (result == 0)
			{
				std::cout << "List is not empty.\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = cslist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}

		}
		else if (cmd.function == "print")
		{

			result = cslist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				cslist.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "reverse")
		{
			result = cslist.reverse(&list);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodes")
		{
			for (int i = 0; i < 9; i++)
			{
				result = cslist.addNodeBack(list, pow(i, 5));
				if (result == 1)
				{
					std::cout << "List is empty.\n";
					break;
				}
			}
			result = cslist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				cslist.print(list);
			}
		}
		else if (cmd.function == "addRandomNodes")
		{
			random random;
			random.initMt();
			for (int i = 0; i < cmd.input1; i++)
			{
				int num = random.getNum(cmd.input2, cmd.input3);
				result = cslist.addNodeBack(list, num);
				if (result == 1)
				{
					std::cout << "List is empty.\n";
					break;
				}
			}
			result = cslist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				cslist.print(list);
			}
		}
		else if (cmd.function == "clearPtr")
		{
			ptr = nullptr;
			std::cout << "Pointer cleared.\n";
		}
		else if (cmd.function == "swap")
		{
			node* ptr1 = nullptr;
			node* ptr2 = nullptr;
			// get ptr1 from position 1.
			result = cslist.returnPtrByPos(list, cmd.input1, ptr1);
			if (result == 0)
			{
				// get ptr2 from position 2.
				result = cslist.returnPtrByPos(list, cmd.input2, ptr2);
				if (result == -1)
				{
					std::cout << "Postition 2 is not in list.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition 1 is not in list.\n";
			}

			// swap ptr1 and ptr2.
			result = cslist.swap(&list, ptr1, ptr2);
			std::cout << "result: " << result << "\n\n";
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer 1 and/or 2 nullptr.\n";
			}
			else if (result == 4)
			{
				std::cout << "Pointers 1 and 2 are the same. No action needed.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer 1 and/or pointer 2 not found in list.\n";
			}
		}
		else if (cmd.function == "shuffle")
		{
			result = cslist.shuffle(&list);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		else if (cmd.function == "bubbleSort")
		{
			result = cslist.bubbleSort(&list, cmd.isAscending, swapCount, sweepCount);
			if (result == 0)
			{
				result = cslist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "swapCount: " << swapCount << '\n';
					std::cout << "sweepCount: " << sweepCount << '\n';
					std::cout << "Node count: " << nodeCount << '\n';
					cslist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Circular singly linked list demo stopped.\n";
}

void cdDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Circular doubly linked list demo started.\n";
	cdList cdlist;
	int result;
	int position;
	int data;
	int nodeCount;
	int swapCount;
	int sweepCount;
	dNode* list = nullptr;
	dNode* ptr = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "init")
		{
			list = cdlist.init(cmd.input1);
			cdlist.size(list, nodeCount);
			std::cout << "Node count: " << nodeCount << '\n';
			cdlist.print(list);
		}
		else if (cmd.function == "addNodeFront")
		{
			result = cdlist.addNodeFront(&list, cmd.input1);
			if (result == 0)
			{
				cdlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				cdlist.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodeBack")
		{
			result = cdlist.addNodeBack(list, cmd.input1);
			if (result == 0)
			{
				cdlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				cdlist.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodeByPos")
		{
			result = cdlist.addNodeByPos(&list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				cdlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				cdlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition is not in list.\n";
			}
		}
		else if (cmd.function == "deleteNodeFront")
		{
			result = cdlist.deleteNodeFront(&list);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeBack")
		{
			result = cdlist.deleteNodeBack(&list);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPos")
		{
			result = cdlist.deleteNodeByPos(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else if (result == 1)
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition is out of bounds.\n";
			}
		}
		else if (cmd.function == "deleteNodeByPtr")
		{
			result = cdlist.deleteNodeByPtr(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "deleteBeforePos")
		{
			result = cdlist.deleteBeforePos(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteBeforePtr")
		{
			result = cdlist.deleteBeforePtr(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "deleteAfterPos")
		{
			result = cdlist.deleteAfterPos(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "deleteAfterPtr")
		{
			result = cdlist.deleteAfterPtr(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "returnPtrByPos")
		{
			result = cdlist.returnPtrByPos(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Pointer to position " << cmd.input1 << ": " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition is out of bounds.\n";
			}
		}
		else if (cmd.function == "returnPosByPtr")
		{
			result = cdlist.returnPosByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Pointer " << ptr << " is in position " << data << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{

				std::cout << "Pointer not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "returnDataByPos")
		{
			result = cdlist.returnDataByPos(list, data, cmd.input1);
			if (result == 0)
			{
				std::cout << "Data in position " << cmd.input1 << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition is out of bounds.\n";
			}
		}
		else if (cmd.function == "returnDataByPtr")
		{
			result = cdlist.returnDataByPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "Data in pointer " << ptr << ": " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n\n";
			}
		}
		else if (cmd.function == "updateDataByPos")
		{
			result = cdlist.updateDataByPos(list, cmd.input1, cmd.input2);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				cdlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Positon is not in list.\n";
			}
		}
		else if (cmd.function == "updateDataByPtr")
		{
			result = cdlist.updateDataByPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "List updated.\n";
				cdlist.print(list);
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "findDataReturnPos")
		{
			result = cdlist.findDataReturnPos(list, cmd.input1, position);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in position " << position << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findDataReturnPtr")
		{
			result = cdlist.findDataReturnPtr(list, cmd.input1, ptr);
			if (result == 0)
			{
				std::cout << "Data '" << cmd.input1 << "' found in pointer " << ptr << ".\n";
			}
			else if (result == 1)
			{
				std::cout << "list is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Data not found in list.\n";
			}
		}
		else if (cmd.function == "findMinReturnPos")
		{
			result = cdlist.findMinReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMinReturnPtr")
		{
			result = cdlist.findMinReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List minimum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPos")
		{
			result = cdlist.findMaxReturnPos(list, data, position);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in position " << position << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findMaxReturnPtr")
		{
			result = cdlist.findMaxReturnPtr(list, data, ptr);
			if (result == 0)
			{
				std::cout << "List maximum " << data << " in pointer " << ptr << ".\n";
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPos")
		{
			result = cdlist.findTailReturnPos(list, position);
			if (result == 0)
			{
				std::cout << "Tail position: " << position << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "findTailReturnPtr")
		{
			result = cdlist.findTailReturnPtr(list, ptr);
			if (result == 0)
			{
				std::cout << "Tail pointer: " << ptr << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "movePosToFront")
		{
			result = cdlist.movePosToFront(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToFront")
		{
			result = cdlist.movePtrToFront(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosToBack")
		{
			result = cdlist.movePosToBack(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrToBack")
		{
			result = cdlist.movePtrToBack(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosUp")
		{
			result = cdlist.movePosUp(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrUp")
		{
			result = cdlist.movePtrUp(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "movePosDown")
		{
			result = cdlist.movePosDown(&list, cmd.input1);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			else if (result == -1)
			{
				std::cout << "Position is not in list.\n";
			}
			else if (result == -2)
			{
				std::cout << "No action needed.\n";
			}
		}
		else if (cmd.function == "movePtrDown")
		{
			result = cdlist.movePtrDown(&list, ptr);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Pointer is not in list.\n";
			}
			else if (result == 2)
			{
				std::cout << "Pointer is null.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = cdlist.clear(&list);
			if (result == 0)
			{
				std::cout << "List is empty.\n";
			}
			else
			{
				std::cout << "List was already empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = cdlist.isEmpty(list);
			if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else
			{
				std::cout << "List is not empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = cdlist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = cdlist.print(list);
			if (result != 0)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "printReverse")
		{
			result = cdlist.printReverse(list);
			if (result != 0)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "reverse")
		{
			result = cdlist.reverse(&list);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addNodes")
		{
			if (list != nullptr)
			{
				for (int i = 0; i < 9; i++)
				{
					cdlist.addNodeBack(list, pow(i, 5));
				}
				cdlist.size(list, nodeCount);
				std::cout << "Node count: " << nodeCount << '\n';
				cdlist.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "addRandomNodes")
		{
			random random;
			random.initMt();
			for (int i = 0; i < cmd.input1; i++)
			{
				int num = random.getNum(cmd.input2, cmd.input3);
				result = cdlist.addNodeBack(list, num);
				if (result == 1)
				{
					std::cout << "List is empty.\n";
					break;
				}
			}
			result = cdlist.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				cdlist.print(list);
			}
		}
		else if (cmd.function == "clearPtr")
		{
			ptr = nullptr;
			std::cout << "Pointer cleared.\n";
		}
		else if (cmd.function == "swap")
		{
			dNode* ptr1 = nullptr;
			dNode* ptr2 = nullptr;
			// get ptr1 from position 1.
			result = cdlist.returnPtrByPos(list, cmd.input1, ptr1);
			if (result == 0)
			{
				// get ptr2 from position 2.
				result = cdlist.returnPtrByPos(list, cmd.input2, ptr2);
				if (result == -1)
				{
					std::cout << "Postition 2 is not in list.\n";
				}
				else if (result == 0)
				{
					// swap ptr1 and ptr2.
					result = cdlist.swap(&list, ptr1, ptr2);
					if (result == 0)
					{
						result = cdlist.size(list, nodeCount);
						if (result == 0)
						{
							std::cout << "Node count: " << nodeCount << '\n';
							cdlist.print(list);
						}
					}
					else if (result == 2)
					{
						std::cout << "Pointer 1 and/or 2 nullptr.\n";
					}
					else if (result == 4)
					{
						std::cout << "Pointers 1 and 2 are the same. No action needed.\n";
					}
					else if (result == 5)
					{
						std::cout << "List has only one node.\n";
					}
					else if (result == -1)
					{
						std::cout << "Pointer 1 and/or pointer 2 not found in list.\n";
					}
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == -1)
			{
				std::cout << "Postition 1 is not in list.\n";
			}
		}
		else if (cmd.function == "shuffle")
		{
			result = cdlist.shuffle(&list);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
		}
		else if (cmd.function == "bubbleSort")
		{
			result = cdlist.bubbleSort(&list, cmd.isAscending, swapCount, sweepCount);
			if (result == 0)
			{
				result = cdlist.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "swapCount: " << swapCount << '\n';
					std::cout << "sweepCount: " << sweepCount << '\n';
					std::cout << "Node count: " << nodeCount << '\n';
					cdlist.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 5)
			{
				std::cout << "List has only one node.\n";
			}
			}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Circular doubly linked list demo stopped.\n";
}

void stackDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Stack demo started.\n";
	stack stack;
	int result;
	int nodeCount;
	int data;
	node* list = NULL;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "push")
		{
			stack.push(&list, cmd.input1);
			stack.print(list);
		}
		else if (cmd.function == "pop")
		{
			result = stack.pop(&list);
			if (result == 0)
			{
				result = stack.print(list);
				if (result == 1)
				{
					std::cout << "Stack is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "Stack is empty.\n";
			}
		}
		else if (cmd.function == "top")
		{
			result = stack.top(list, data);
			if (result == 0)
			{
				std::cout << "Top node: " << data << '\n';
			}
			else if (result == 1)
			{
				std::cout << "Stack is empty.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = stack.clear(&list);
			if (result == 0)
			{
				std::cout << "Stack cleared.\n";
			}
			else
			{
				std::cout << "Stack is empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = stack.isEmpty(list);
			if (result == 0)
			{
				std::cout << "Stack is not empty.\n";
			}
			else
			{
				std::cout << "Stack is empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = stack.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Stack size: " << nodeCount << '\n';
			}
			else if (result == 1)
			{
				std::cout << "Stack is empty.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = stack.print(list);
			if (result == 1)
			{
				std::cout << "Stack is empty.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Stack demo stopped.\n";
}

void queueDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Queue demo started.\n";
	queue q;
	int result;
	int nodeCount;
	int data;
	dNode* list = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "push")
		{
			result = q.push(list, cmd.input1);
			q.print(list);
		}
		else if (cmd.function == "pop")
		{
			result = q.pop(&list);
			if (result == 0)
			{
				result = q.print(list);
				if (result != 0)
				{
					std::cout << "List is empty.\n";
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "front")
		{
			result = q.front(list, data);
			if (result == 0)
			{
				std::cout << "First element in queue: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "back")
		{
			result = q.back(list, data);
			if (result == 0)
			{
				std::cout << "Last element in queue: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = q.clear(&list);
			if (result == 0)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 1)
			{
				std::cout << "List was already empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = q.isEmpty(list);
			if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else
			{
				std::cout << "List is not empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = q.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = q.print(list);
			if (result != 0)
			{
				std::cout << "List is empty.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Queue demo stopped.\n";
}

void dequeDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Deque demo start.\n";
	deque dq;
	int result;
	int nodeCount;
	int data;
	node* list = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "front")
		{
			result = dq.front(list, data);
			if (result == 0)
			{
				std::cout << "First element in queue: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "back")
		{
			result = dq.back(list, data);
			if (result == 0)
			{
				std::cout << "Last element in queue: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "pushFront")
		{
			dq.push_front(&list, cmd.input1);
			result = dq.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				dq.print(list);
			}
		}
		else if (cmd.function == "popFront")
		{
			result = result = dq.pop_front(&list);
			if (result == 0)
			{
				result = dq.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dq.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "pushBack")
		{
			dq.push_back(&list, cmd.input1);
			result = dq.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				dq.print(list);
			}
		}
		else if (cmd.function == "popBack")
		{
			result = dq.pop_back(&list);
			if (result == 0)
			{
				result = dq.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					dq.print(list);
				}
				else
				{
					std::cout << "List is empty.\n";
				}
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = dq.clear(&list);
			if (result == 0)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 1)
			{
				std::cout << "List was already empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = dq.isEmpty(list);
			if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else
			{
				std::cout << "List is not empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = dq.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = dq.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
				dq.print(list);
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Deque demo stopped.\n";
}

void priorityQueueDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "Priority Queue demo started.\n";
	priorityQueue pq;
	int result;
	int nodeCount;
	int data;
	node* list = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "set")
		{
			result = pq.set(&list, cmd.isAscending);
			if (result == 0)
			{
				result = pq.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					pq.print(list);
				}
				else if (result == 1)
				{
					std::cout << "List is empty.\n";
				}
			}
		}
		else if (cmd.function == "top")
		{
			result = pq.top(list, data);
			if (result == 0)
			{
				std::cout << "First element in queue: " << data << '\n';
			}
			else
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "push")
		{
			result = pq.push(&list, cmd.input1);
			if (result == 0)
			{
				result = pq.size(list, nodeCount);
				if (result == 0)
				{
					std::cout << "Node count: " << nodeCount << '\n';
					pq.print(list);
				}
				else if (result == 1)
				{
					std::cout << "List is empty.\n";
				}
			}
		}
		else if (cmd.function == "pop")
		{
			result = pq.pop(&list);
			if (result == 0)
			{
				if (result == 0)
				{
					pq.size(list, nodeCount);
					std::cout << "Node count: " << nodeCount << '\n';
					pq.print(list);
				}
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = pq.clear(&list);
			if (result == 0)
			{
				std::cout << "List is empty.\n";
			}
			else if (result == 1)
			{
				std::cout << "List was already empty.\n";
			}
		}
		else if (cmd.function == "isEmpty")
		{
			result = pq.isEmpty(list);
			if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
			else
			{
				std::cout << "List is not empty.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = pq.size(list, nodeCount);
			if (result == 0)
			{
				std::cout << "Node count: " << nodeCount << '\n';
			}
			else if (result == 1)
			{
				std::cout << "List is empty.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = pq.print(list);
			if (result != 0)
			{
				std::cout << "List is empty.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "Priority Queue demo stopped.\n";
}

void fifoDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	std::cout << "FIFO demo started.\n";
	fifo fifo;
	int result;
	int wordCount;
	int data;
	node* list = nullptr;

	std::unique_lock<std::mutex> lk(m);
	cv.notify_one();
	while (demoStatus)
	{
		cv.wait(lk);
		std::cout << '\n';
		if (cmd.function == "config")
		{
			result = fifo.config(cmd.input1);
			if (result == 7)
			{
				std::cout << "FIFO not configured: depth out of bounds.\n\n";
			}
		}
		else if (cmd.function == "write")
		{
			result = fifo.wr_en(list, cmd.input1);
			if (result == 0)
			{
				result = fifo.data_count(list, wordCount);
				if (result >= 0 and result < 4)
				{
					std::cout << "Word count: " << wordCount << '\n';
					fifo.print(list);
				}
			}
			else if (result == 6)
			{
				std::cout << "FIFO overflow.\n";
			}
			else if (result == 7)
			{
				std::cout << "FIFO not configured.\n";
			}
		}
		else if (cmd.function == "read")
		{
			result = fifo.rd_en(&list, data);
			if (result == 0)
			{
				std::cout << "FIFO output: " << data << '\n';
			}
			else if (result == 5)
			{
				std::cout << "FIFO underflow.\n";
			}
			else if (result == 7)
			{
				std::cout << "FIFO not configured.\n";
			}
		}
		else if (cmd.function == "clear")
		{
			result = fifo.rst(&list);
			if (result == 0)
			{
				std::cout << "FIFO cleared.\n";
			}
			else if (result == 4)
			{
				std::cout << "FIFO is empty.\n";
			}
			else if (result == 7)
			{
				std::cout << "FIFO not configured.\n";
			}
		}
		else if (cmd.function == "size")
		{
			result = fifo.data_count(list, wordCount);
			if (result == 0)
			{
				std::cout << "Word count: " << wordCount << "\n\n";
			}
			else if (result == 4)
			{
				std::cout << "FIFO empty.\n\n";
			}
			else if (result == 3)
			{
				std::cout << "FIFO almost empty.\n\n";
			}
			else if (result == 2)
			{
				std::cout << "FIFO almost full. Word count: " << wordCount << "\n\n";
			}
			else if (result == 1)
			{
				std::cout << "FIFO full. Word count: " << wordCount << "\n\n";
			}
			else if (result == 7)
			{
				std::cout << "FIFO not configured.\n";
			}
		}
		else if (cmd.function == "print")
		{
			result = fifo.data_count(list, wordCount);
			if (result >= 0 and result < 4)
			{
				std::cout << "Word count: " << wordCount << '\n';
				fifo.print(list);
			}
			else if (result == 4)
			{
				std::cout << "FIFO is empty.\n";
			}
			else if (result == 7)
			{
				std::cout << "FIFO not configured.\n";
			}
		}
		cv.notify_one();
	}
	cv.notify_one();
	std::cout << "FIFO demo stopped.\n";
}