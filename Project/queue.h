#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"

template<class ItemType>
class LinkedQueue 
{
private:
	// The queue is implemented as a chain of linked nodes that has
	// two external pointers, a head pointer for the front of the
	// queue and a tail pointer for the back of the queue.
	Node<ItemType>* backPtr;
	Node<ItemType>* frontPtr;
	int itemCount; //added
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& aQueue);
	virtual ~LinkedQueue();
	int getLength() const; //added
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const;
	void print() const;
};

template<class ItemType>
 LinkedQueue<ItemType>::LinkedQueue()
	: backPtr(nullptr), frontPtr(nullptr), itemCount(0) //added
{
}


 template<class ItemType>
 void LinkedQueue<ItemType>::print() const//done print here
 {

	 if (!isEmpty())
	 {
		 Node<ItemType>* tmp = frontPtr;
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
	 return;
 }
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& aQueue)
{
	Node<ItemType>* originChainPtr = aQueue.frontPtr;
	itemCount = aQueue.itemCount; //added
	if (originChainPtr == nullptr)
	{
		frontPtr = nullptr;
		backPtr = nullptr;
		return;
	}

	while (originChainPtr != nullptr)
	{
		enqueue(originChainPtr->getItem());
		originChainPtr = originChainPtr->getNext();
	}
}

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
	while (!isEmpty())
	{
		dequeue();
	}
}

template<class ItemType>
inline bool LinkedQueue<ItemType>::isEmpty() const
{
	return frontPtr == nullptr;
}

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	if (isEmpty())
		frontPtr = newNodePtr;
	else
		backPtr->setNext(newNodePtr);
	backPtr = newNodePtr;
	itemCount++;//added
	return true;
}


template<class ItemType>//added
int LinkedQueue<ItemType>::getLength() const
{
	return itemCount;
}


template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result = false;

	if (!isEmpty())
	{
		// Queue is not empty: remove front
		Node<ItemType>* nodeToDeletePtr = frontPtr;

		if (frontPtr == backPtr) // Special case: one node in queue
		{
			frontPtr = nullptr;
			backPtr = nullptr;
		}
		else
			frontPtr = frontPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		itemCount--;////addded noowww
		result = true;
	}
	return result;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const
{
	return frontPtr->getItem();	// didn't check for empty because it's in the specification as a @pre
}
#endif