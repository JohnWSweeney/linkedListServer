#include "demos.h"
#include "atomicBool.h"
#include "random.h"
#include "sList.h"
#include "dList.h"

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
	while (status)
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
	while (status)
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