#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "Node.h"
#include "process.h"
#include <iostream>
using namespace std;
template<class ItemType>
class LinkedList
{
protected:
	Node<ItemType>* headPtr, *tailptr;
	int itemCount;

	Node<ItemType>* getNodeAt(int position) const;
public:
	LinkedList();
	LinkedList(const LinkedList<ItemType>& aList);
	virtual ~LinkedList();
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	void print() const;

	ItemType getEntry(int position) const;//throw(PrecondViolatedExcep);

	void setEntry(int position, const ItemType& newEntry);// i made it
		//throw(PrecondViolatedExcep);
};

template< class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0), tailptr(nullptr)
{
}

template< class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template< class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return (itemCount);
}

template< class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType& newEntry)
{
	if ((position >= 1) && (position <= itemCount))
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		nodePtr->setItem(newEntry);
	}
	else return;
}


template< class ItemType>
void LinkedList<ItemType>::print() const
{
	if (!isEmpty())
	{
		Node<ItemType>* tmp = headPtr;
		while (tmp)
		{
			cout << *tmp->getItem();
			tmp = tmp->getNext();
			if (tmp)
			{
				cout << ", ";
			}
		}
	}
}

//template<>
//void  print() const
//{
//	if (!isEmpty())
//	{
//		Node<process*>* tmp = headPtr;
//		while (tmp)
//		{
//			cout << *tmp->getItem();
//			tmp = tmp->getNext();
//			if (tmp)
//			{
//				cout << ", ";
//			}
//		}
//	}
//}


template< class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
///throw(PrecondViolatedExcep)
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
	else
	{
		//there was an exception we deleted it
		////throw(PrecondViolatedExcep(message));
	}

}

template< class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	// Debugging check of precondition
	//assert((position >= 1) && (position <= itemCount));                           ///////first edition
	// Count from the beginning of the chain
	if ((position >= 1) && (position <= itemCount))////////////
	{
		Node<ItemType>* curPtr = headPtr;
		for (int skip = 1; skip < position; skip++)
			curPtr = curPtr->getNext();
		return curPtr;
	}
	else return nullptr;/////////////
}

template< class ItemType>
bool LinkedList<ItemType>::insert(int newPosition,
	const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) &&//not -ve or 0 pos
		(newPosition <= itemCount + 1);//alternative or insert end
	if (ableToInsert)
	{
		// Create a new node containing the new entry
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
		// Attach new node to chain
		if (newPosition == 1)
		{
			// Insert new node at beginning of chain
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
			tailptr = headPtr;
		}
		else if(newPosition != itemCount + 1)
		{
			// Find node that will be before new node
			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
			tailptr = newNodePtr;
		} // end if
		else
		{
			tailptr->setNext(newNodePtr);
			newNodePtr->setNext(nullptr);
			tailptr = newNodePtr;
		}
		
		itemCount++; // Increase count of entries
	} // end if
	return ableToInsert;
} // end insert 


template< class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr;
		if (position == 1)
		{
			// Remove the first node in the chain
			curPtr = headPtr; // Save pointer to node
			headPtr = headPtr->getNext();
			if (itemCount == 1)
				tailptr = headPtr;
		}
		else
		{
			
			// Find node that is before the one to delete
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			// Point to node to delete
			curPtr = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the
			 // prior node with the one after
			prevPtr->setNext(curPtr->getNext());
			if (position == itemCount)
				tailptr = prevPtr;

		} // end if
	   // Return node to system
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		itemCount-- ; // Decrease count of entries
	} // end if
	return ableToRemove;
} // end remove 

template< class ItemType>
void LinkedList<ItemType>::clear()
{
	while (!isEmpty())
		remove(1);///////removing at pos 1 till the list ends
}

template< class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}






#endif 