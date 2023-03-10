#ifndef LIST_HPP
#define LIST_HPP


#include <stdexcept>
#include <ostream>
#include <iostream>


template<typename T>
struct Node
{
	T value;
	Node<T>* next;

	Node() : value{}, next{ nullptr } { std::cout << "create\n"; }
	Node(T val, Node<T>* nxt = nullptr) : value{ val }, next{ nxt } { std::cout << "create\n"; }

	~Node() { std::cout << "delete\n"; }
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

	Iterator<T>& operator ++ ();
	Iterator<T> operator ++ (int);

	operator Node<T>* () { return curNode; }

	Iterator<T> operator + (const size_t& value);

	bool operator == (const Iterator<T>& other) { return curNode == other.curNode; }
	bool operator != (const Iterator<T>& other) { return curNode != other.curNode; }
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

	ConstIterator<T>& operator ++ ();
	ConstIterator<T> operator ++ (int);

	operator Node<T>* () { return curNode; }

	ConstIterator<T> operator + (const size_t& value);

	bool operator == (const ConstIterator<T>& other) { return curNode == other.curNode; }
	bool operator != (const ConstIterator<T>& other) { return curNode != other.curNode; }
};




template<typename T>
class List
{
private:
	Node<T>* mHead;
	Node<T>* mTail;
	size_t mSize;

private:
	void copyOtherList(const List<T>& other);
	void throwExceptionIfEmpty() const;

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


	void push_back(T value);
	void pop_back();


	void push_front(T value);
	void pop_front();


	bool empty() const noexcept { return mHead->next == nullptr; }
	bool find(T value) const noexcept;
	void clear();


	Iterator<T> begin() noexcept { return Iterator<T>(mHead->next); }
	Iterator<T> end() noexcept { return Iterator<T>(mHead); }


	ConstIterator<T> cbegin() const noexcept { return ConstIterator<T>(mHead->next); }
	ConstIterator<T> cend() const noexcept { return ConstIterator<T>(mHead); }


	List<T>& operator = (const List<T>& other);
	friend std::ostream& operator << (std::ostream& out, const List<T>& list)
	{
		if (list.empty()) return out;

		for (auto it = list.cbegin(); it != list.cend(); ++it)
			out << *it << ' ';

		return out;
	}
};




/////////////////////// Iterator ///////////////////////

template<typename T>
inline Iterator<T>& Iterator<T>::operator++()
{
	if (curNode == nullptr) return *this;

	curNode = curNode->next;

	return *this;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++(int)
{
	if (curNode == nullptr) return *this;

	Iterator<T> newIt(curNode);

	++(*this);

	return newIt;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator+(const size_t& value)
{
	if (curNode == nullptr) return *this;

	Iterator<T> newIt(curNode);

	for (size_t i = 0; i < value; ++i)
		newIt.curNode = newIt.curNode->next;

	return newIt;
}




/////////////////////// ConstIterator ///////////////////////

template<typename T>
inline ConstIterator<T>& ConstIterator<T>::operator++()
{
	if (curNode == nullptr) return *this;

	curNode = curNode->next;

	return *this;
}

template<typename T>
inline ConstIterator<T> ConstIterator<T>::operator++(int)
{
	if (curNode == nullptr) return *this;

	ConstIterator<T> newIt(curNode);

	++(*this);

	return newIt;
}

template<typename T>
inline ConstIterator<T> ConstIterator<T>::operator+(const size_t& value)
{
	if (curNode == nullptr) return *this;

	ConstIterator<T> newIt(curNode);

	for (size_t i = 0; i < value; ++i)
		newIt.curNode = newIt.curNode->next;

	return newIt;
}




/////////////////////// List ///////////////////////

template<typename T>
inline void List<T>::copyOtherList(const List<T>& other)
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

template<typename T>
inline void List<T>::throwExceptionIfEmpty() const
{
	if (empty())
		throw std::logic_error{ "list is empty" };
}

template<typename T>
inline void List<T>::push_back(T value)
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

template<typename T>
inline void List<T>::pop_back()
{
	throwExceptionIfEmpty();

	Node<T>* newBackNode = begin() + (mSize - 2);
	mTail = newBackNode;

	delete newBackNode->next;
	newBackNode->next = mHead;

	--mSize;
}

template<typename T>
inline void List<T>::push_front(T value)
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

template<typename T>
inline void List<T>::pop_front()
{
	throwExceptionIfEmpty();

	Node<T>* newFrontNode = begin() + 1;

	delete mHead->next;
	mHead->next = newFrontNode;

	--mSize;
}

template<typename T>
inline bool List<T>::find(T value) const noexcept
{
	if (empty()) return false;

	for (auto it = cbegin(); it != cend(); ++it)
		if (*it == value) return true;

	return false;
}

template<typename T>
inline void List<T>::clear()
{
	if (empty()) return;

	for (auto it = begin(); it != end();)
	{
		Node<T>* delNode = it++;
		delete delNode;
	}

	mHead->next = mTail = nullptr;
	mSize = 0;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;

	clear();

	if (other.empty()) return *this;

	copyOtherList(other);

	return *this;
}


#endif // LIST_HPP