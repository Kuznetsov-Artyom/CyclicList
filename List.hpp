#ifndef LIST_HPP
#define LIST_HPP


#include <stdexcept>
#include <ostream>



template<typename T>
struct Node
{
	T value;
	Node<T>* next;

	Node() : value{}, next{ nullptr } {}
	Node(T val, Node<T>* nxt = nullptr) : value{ val }, next{ nxt } {}
};




template<typename T>
class Iterator
{
private:
	Node<T>* curNode;

public:
	Iterator(Node<T>* node = nullptr) : curNode{ node } {}

	T& operator * () { return curNode->value; }
	Node<T>* operator -> () { return curNode; }

	Iterator<T>& operator ++ ()
	{
		if (curNode == nullptr) return *this;

		curNode = curNode->next;

		return *this;
	}
	Iterator<T> operator ++ (int)
	{
		if (curNode == nullptr) return *this;

		Iterator<T> newIt(curNode);

		++(*this);

		return newIt;
	}

	operator Node<T>* () { return curNode; }

	Iterator<T> operator + (const size_t& value)
	{
		if (curNode == nullptr) return *this;

		Iterator<T> newIt(curNode);

		for (size_t i = 0; i < value; ++i)
			newIt.curNode = newIt.curNode->next;

		return newIt;
	}

	bool operator == (const Iterator<T>& other)
	{
		return curNode == other.curNode;
	}
	bool operator != (const Iterator<T>& other)
	{
		return curNode != other.curNode;
	}
};

template<typename T>
class ConstIterator
{
private:
	Node<T>* curNode;

public:
	ConstIterator(Node<T>* node = nullptr) : curNode{ node } {}

	const T& operator * () { return curNode->value; }
	Node<T>* operator -> () { return curNode; }

	ConstIterator<T>& operator ++ ()
	{
		if (curNode == nullptr) return *this;

		curNode = curNode->next;

		return *this;
	}
	ConstIterator<T> operator ++ (int)
	{
		if (curNode == nullptr) return *this;

		ConstIterator<T> newIt(curNode);

		++(*this);

		return newIt;
	}

	operator Node<T>* () { return curNode; }

	ConstIterator<T> operator + (const size_t& value)
	{
		if (curNode == nullptr) return *this;

		ConstIterator<T> newIt(curNode);

		for (size_t i = 0; i < value; ++i)
			newIt.curNode = newIt.curNode->next;

		return newIt;
	}

	bool operator == (const ConstIterator<T>& other)
	{
		return curNode == other.curNode;
	}
	bool operator != (const ConstIterator<T>& other)
	{
		return curNode != other.curNode;
	}
};




template<typename T>
class List
{
private:
	Node<T>* mHead;
	Node<T>* mTail;
	size_t mSize;

private:
	void copyOtherList(const List<T>& other)
	{
		Node<T>* copyNode = new Node<T>(other.cbegin()->value, nullptr);

		mHead->next = copyNode;
		++mSize;

		for (auto it = other.cbegin() + 1; it != other.cend(); ++it)
		{
			copyNode->next = new Node<T>(*it);
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
	List() : mHead{ new Node<T> }, mTail{ nullptr }, mSize{ 0 } {}
	List(const List<T>& other) : List()
	{
		if (other.empty()) return;

		copyOtherList(other);
	}


	~List()
	{
		if (!empty()) clear();
		delete mHead;
	}


	T back() const
	{
		throwExceptionIfEmpty();

		return mTail->value;
	}
	T front() const
	{
		throwExceptionIfEmpty();

		return mHead->next->value;
	}
	size_t size() const noexcept { return mSize; }


	void push_back(T value)
	{
		Node<T>* newNode = new Node<T>(value);
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

		Node<T>* newBackNode = begin() + (mSize - 2);
		mTail = newBackNode;

		delete newBackNode->next;
		newBackNode->next = mHead;

		--mSize;
	}


	void push_front(T value)
	{
		Node<T>* newNode = new Node<T>(value);
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

		Node<T>* newFrontNode = begin() + 1;

		delete mHead->next;
		mHead->next = newFrontNode;

		--mSize;
	}


	bool empty() const noexcept { return mHead->next == nullptr; }
	bool find(T value) const noexcept
	{
		if (empty()) return false;

		for (auto it = cbegin(); it != cend(); ++it)
			if (*it == value) return true;

		return false;
	}
	void clear()
	{
		if (empty()) return;

		Node<T>* current = mHead->next;

		do
		{
			Node<T>* next = current->next;
			delete current;
			current = next;

		} while (current != mHead);

		mHead->next = mTail = nullptr;
		mSize = 0;
	}


	Iterator<T> begin() noexcept { return Iterator<T>(mHead->next); }
	Iterator<T> end() noexcept { return Iterator<T>(mHead); }
	ConstIterator<T> cbegin() const noexcept { return ConstIterator<T>(mHead->next); }
	ConstIterator<T> cend() const noexcept { return ConstIterator<T>(mHead); }


	List<T>& operator = (const List<T>& other)
	{
		if (this == &other) return *this;

		clear();

		if (other.empty()) return *this;

		copyOtherList(other);

		return *this;
	}
	friend std::ostream& operator << (std::ostream& out, const List<T>& list)
	{
		if (list.empty()) return out;

		for (auto it = list.cbegin(); it != list.cend(); ++it)
			out << *it << ' ';

		return out;
	}
};



#endif // LIST_HPP
