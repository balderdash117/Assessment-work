#pragma once
/*Written by Ben Alder*/
/*with the help of Sebastion Toy and Aaron(Teacher)*/
/*Completed on 30/6/2017*/

#include <assert.h>

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

	unsigned int size = 0;

public:

	unsigned int getSize()
	{
		return size;
	}

	struct LinkIterator
	{
		LinkIterator() : ptr(nullptr) {}
		LinkIterator(LinkNode* _ptr) : ptr(_ptr) {}

		LinkNode*	ptr;

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
			auto returnValue = ptr->value;
			return returnValue;
		}

		bool operator== (const LinkIterator &rhs)
		{
			return ptr == rhs.ptr;
		}
			
		LinkIterator operator-- ()
		{
			return ptr = ptr->Previous;
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

		++size;
	}

	void popBack()
	{
		assert(size != 0 && "Cant pop an item from an empty collection");

		if (m_first == m_last)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
		}

		else
		{
			LinkNode *prev = m_last->Previous;
			prev->Next = nullptr;
			delete m_last;

			m_last = prev;
		}
		--size;
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

	LinkIterator last() {
		return LinkIterator(m_last);
	}

	LinkIterator FindFirstValue(const T& value)
	{
		for (auto iter = begin(); iter != end(); iter++)
		{
			if (*iter == value)
				return iter;
		}

		return end();
	}

	void insert(LinkIterator iterLocation, const T &value)
	{

		if (iterLocation == begin())
		{
			pushFront(value);
			return;
		}

		else if (iterLocation == end())
		{
			pushBack(value);
			return;
		}

		LinkNode *temp = new LinkNode(value);

		LinkNode *ln = iterLocation.ptr;
		ln->Previous->Next  = temp;
		temp->Previous	    = ln->Previous;

		ln->Previous	    = temp;
		temp->Next			= ln;

		++size;
	}

	LinkIterator erase(LinkIterator iter)
	{

		if (m_first == m_last)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
			--size;
			return last();
		}

		else if (iter == begin())
		{
			popFront();
			return begin();
		}

		else if (iter == last())
		{
			popBack();
			return last();
		}

		LinkNode *ln = iter.ptr;


		if (ln->Next == nullptr)
		{
			popBack();
			return last();
		}
		else
		{
			ln->Previous->Next = ln->Next;
			ln->Next->Previous = ln->Previous;

			LinkIterator iterReturn(ln->Next);

			delete ln;
			--size;
			return iterReturn;
		}
	}

	void remove(const T &value)
	{
		auto iter = FindFirstValue(value);

		erase(iter);
	}

	void pushFront(T _item)
	{
		LinkNode *temp = new LinkNode(_item);

		if (m_first == nullptr)
		{
			m_first = temp;
			m_last = temp;
		}
		else
		{
			temp->Next = m_first;
			m_first->Previous = temp;
			temp->Previous = nullptr;
			
			m_first = temp;
		}

		++size;
	}

	void popFront()
	{
		assert(begin() != end() && "Cant pop an item from an empty collection");

		if (m_first == m_last)
		{
			delete m_first;
			m_first = nullptr;
			m_last = nullptr;
		}

		else
		{
			m_first = m_first->Next;
			delete m_first->Previous;
			m_first->Previous = nullptr;
		}
		--size;
	}

protected:
	LinkNode  *m_first = nullptr;
	LinkNode  *m_last = nullptr;

};