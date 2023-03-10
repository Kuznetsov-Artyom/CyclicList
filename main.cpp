#include <iostream>
#include <stdexcept>
#include <vector>

struct Node
{
	int value;
	Node* next;

	Node(int val = 0, Node* nxt = nullptr) : value{ val }, next{ nxt }
	{
		std::cout << "Create Node\n";
	}
	~Node()
	{
		std::cout << "Delete Node\n";
	}
};


class Iterator
{
private:
	Node* curNode;

public:
	Iterator(Node* node = nullptr) : curNode{ node } {}

	int& operator * () { return curNode->value; }
	Node* operator -> () { return curNode; }

	Iterator& operator ++ ()
	{
		if (curNode == nullptr) return *this;

		curNode = curNode->next;

		return *this;
	}
	Iterator operator ++ (int)
	{
		if (curNode == nullptr) return *this;

		Iterator newIt(curNode);

		++(*this);

		return newIt;
	}

	operator Node* () { return curNode; }

	Iterator operator + (const size_t& value)
	{
		if (curNode == nullptr) return *this;

		Iterator newIt(curNode);

		for (size_t i = 0; i < value; ++i)
			newIt.curNode = newIt.curNode->next;

		return newIt;
	}

	bool operator == (const Iterator& other)
	{
		return curNode == other.curNode;
	}
	bool operator != (const Iterator& other)
	{
		return curNode != other.curNode;
	}
};
class ConstIterator
{
private:
	Node* curNode;

public:
	ConstIterator(Node* node = nullptr) : curNode{ node } {}

	const int& operator * () { return curNode->value; }
	Node* operator -> () { return curNode; }

	ConstIterator& operator ++ ()
	{
		if (curNode == nullptr) return *this;

		curNode = curNode->next;

		return *this;
	}
	ConstIterator operator ++ (int)
	{
		if (curNode == nullptr) return *this;

		ConstIterator newIt(curNode);

		++(*this);

		return newIt;
	}

	operator Node* () { return curNode; }

	ConstIterator operator + (const size_t& value)
	{
		if (curNode == nullptr) return *this;

		ConstIterator newIt(curNode);

		for (size_t i = 0; i < value; ++i)
			newIt.curNode = newIt.curNode->next;

		return newIt;
	}

	bool operator == (const ConstIterator& other)
	{
		return curNode == other.curNode;
	}
	bool operator != (const ConstIterator& other)
	{
		return curNode != other.curNode;
	}
};





class List
{
private:
	Node* mHead;
	Node* mTail;
	size_t mSize;

private:
	void copyOtherList(const List& other)
	{
		Node* copyNode = new Node(other.cbegin()->value);

		mHead->next = copyNode;
		++mSize;

		for (auto it = other.cbegin() + 1; it != other.cend(); ++it)
		{
			copyNode->next = new Node(*it);
			copyNode = copyNode->next;
			++mSize;
		}

		copyNode->next = mHead;
		mTail = copyNode;
	}
	void throwExceptionIfEmpty() const
	{
		if (empty())
			throw std::logic_error{ "list is empty" };
	}

public:
	List() : mHead{ new Node() }, mTail{ nullptr }, mSize{ 0 } {}
	List(const List& other) : List()
	{
		if (other.empty()) return;

		copyOtherList(other);
	}


	~List()
	{
		if (!empty()) clear();
		delete mHead;
	}


	int back() const
	{
		throwExceptionIfEmpty();

		return mTail->value;
	}
	int front() const
	{
		throwExceptionIfEmpty();

		return mHead->next->value;
	}
	size_t size() const noexcept { return mSize; }


	void push_back(int value)
	{
		Node* newNode = new Node(value);
		++mSize;

		if (empty())
		{
			mHead->next = mTail = newNode;
		}
		else
		{
			mTail->next = newNode;
			mTail = newNode;
			mTail->next = mHead;
		}
	}
	void pop_back()
	{
		throwExceptionIfEmpty();

		Node* newBackNode = begin() + (mSize - 2);
		mTail = newBackNode;

		delete newBackNode->next;
		newBackNode->next = mHead;

		--mSize;
	}


	void push_front(int value)
	{
		Node* newNode = new Node(value);
		++mSize;

		if (empty())
		{
			mHead->next = mTail = newNode;
		}
		else
		{
			newNode->next = mHead->next;
			mHead->next = newNode;
		}
	}
	void pop_front()
	{
		throwExceptionIfEmpty();

		Node* newFrontNode = begin() + 1;

		delete mHead->next;
		mHead->next = newFrontNode;

		--mSize;
	}


	bool empty() const noexcept { return mHead->next == nullptr; }
	bool find(int value) const noexcept
	{
		if (empty()) return false;

		for (auto it = cbegin(); it != cend(); ++it)
			if (*it == value) return true;

		return false;
	}
	void clear()
	{
		if (empty()) return;

		Node* current = mHead->next;

		do
		{
			Node* next = current->next;
			delete current;
			current = next;

		} while (current != mHead);

		mHead->next = mTail = nullptr;
		mSize = 0;
	}


	Iterator begin() noexcept { return Iterator(mHead->next); }
	Iterator end() noexcept { return Iterator(mHead); }
	ConstIterator cbegin() const noexcept { return ConstIterator(mHead->next); }
	ConstIterator cend() const noexcept { return ConstIterator(mHead); }


	List& operator = (const List& other)
	{
		if (this == &other) return *this;

		clear();

		if (other.empty()) return *this;

		copyOtherList(other);

		return *this;
	}
	friend std::ostream& operator << (std::ostream& out, const List& list);
};


std::ostream& operator << (std::ostream& out, const List& list)
{
	if (list.empty()) return out;

	for (auto it = list.cbegin(); it != list.cend(); ++it)
		out << *it << ' ';

	return out;
}





void printList(const List& list)
{
	if (list.empty()) std::cout << "List is empty\n";
	else std::cout << "Elements list: " << list << '\n';
}



int main(int argc, char* argv[])
{
	List list;

	printList(list);

	int countElem = 5;

	for (int i = 0; i < countElem; ++i)
		list.push_back(i + 1);

	printList(list);

	list.pop_back();

	printList(list);

	list.push_front(100);

	printList(list);

	list.pop_front();

	printList(list);




	return 0;
}