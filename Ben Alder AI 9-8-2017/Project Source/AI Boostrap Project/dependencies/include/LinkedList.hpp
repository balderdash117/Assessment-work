#pragma once

nclude <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <string>

using std::string;

/*

LinkedList<Person>; 

for (int i = 0; i < 100; ++i) {
	LinkedList.PushBack(i);
}

for (auto iter : ll) {
	node = Person;
}

for (auto iter = ll.begin(); iter != ll.end(); iter++) {
	node = iter->value;
}


*/

template <class T> class LinkedList
{
private:
	struct LinkNode
	{
		LinkNode(T _value) : value(_value) {}

		LinkNode  *Next = nullptr;
		LinkNode  *Previous = nullptr;

		T value;
	};

	struct LinkIterator
	{
		LinkIterator(LinkNode* _ptr) : ptr(_ptr) {}

		LinkNode*	ptr = nullptr;

		// Operator overloads for ranged-for functionality
		bool operator != (LinkIterator _LIter)
		{
			if (ptr == _LIter.ptr)
			{
				return false;
			}
			else
			{
				return true;
			}

			//one line version
			//return ptr != _LIter.ptr
		}

		// Pre-fix (++LinkIterator)
		LinkIterator& operator++()
		{
			// Point at the next node in the Linked List
			ptr = ptr->Next;
			return *this;
		}

		// Post-fix (LinkIterator++ int) 
		LinkIterator operator++(int)
		{
			LinkIterator tmp = *this; // this (our current LinkIterator) is automatically a pointer so de-reference it
			++*this;				  // Call our pre-fix operator to simplify code
			return tmp;				  // Return alias of LinkIterator pre-operation
		}

		// Overload the de-reference operator (*LinkIterator) so that it returns the value LinkNode is holding onto.
		T operator * ()
		{
			return ptr->value;
		}
	};


public:		
	LinkedList() = default;
	~LinkedList() = default;

	void pushBack(T _item)
	{
		LinkNode *temp = new LinkNode(_item);

		if (m_first == nullptr)
		{
			m_first = temp;
			m_last = temp;
		}
		else
		{
			m_last->Next = temp;
			temp->Previous = m_last;

			m_last = temp;
		}
	}

	void popBack()
	{
		LinkNode *prev = m_last->Previous;
		prev->Next = nullptr;
		delete m_last;

		m_last = prev;
	}


	/*
	LinkIterator thing = linkedlist.begin();

	thing = random garbage;
	*/
	LinkIterator begin() {
		return LinkIterator(m_first);
	}

	// End will be the next of the final node (in this case it's always nullptr)
	LinkIterator end() {
		return LinkIterator(nullptr);   // Same as LinkIterator(LastNode->NextNode);
	}

	LinkIterator insert()
	{

		//if (FirstNode == nullptr)
		//{
		//	pushBack();
		//	return;
		//}

		//LinkNode *temp = new LinkNode(_item);


	}

	LinkIterator erase()
	{

	}

	LinkIterator remove()
	{
		 
	}

protected:
	LinkNode  *currentptr = nullptr;
	LinkNode  *m_first = nullptr;
	LinkNode  *m_last = nullptr;
};