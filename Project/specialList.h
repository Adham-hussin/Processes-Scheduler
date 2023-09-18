#pragma once
#include "list.h"

class LinkedProcess : public LinkedList<process*>
{
public:
	LinkedProcess()
	{
		headPtr = nullptr;
		tailptr = nullptr;
		itemCount = 0;
	}
	int searchID(int id) 
	{ 

		if (!headPtr)
			return 0;
		Node<process*>* ptr = headPtr;
		int i = 1;
		while (ptr)
		{
			if (ptr->getItem()->getPID() == id)
			{
				/*process* tmprocess = ptr->getItem();
				ptr->setItem(ptr->getNext()->getItem());
				Node<process*>* temp = ptr->getNext();
				ptr->setNext(temp->getNext());
				delete temp;*/
				return i;
			}
			ptr = ptr->getNext();
			i++;
		}
		return 0;
	}
	
};