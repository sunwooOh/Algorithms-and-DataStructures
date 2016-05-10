#include<iostream>
template<class T>
class List {
public:
	class Node {
	public:
		Node(T x = 0, Node* ptr = NULL) { data = x; next = ptr; }
		T getData() { return data; }
		Node* getNext() { return next; }
		void setData(T x) { data = x; } // not used in this List class
		void setNext(Node* ptr) { next = ptr; }

	private:
		T data;
		Node* next;
	};

	List() {
		head_ptr = NULL; tail_ptr = NULL;
		numOfItems = 0;
	}
	int size() { return numOfItems; }
	Node* getHead() { return head_ptr; }
	Node* getTail() { return tail_ptr; }
	bool isEmpty() { return (numOfItems == 0); }
	Node* search(T x) {
		Node* currentPtr = getHead();
		while (currentPtr)
			if (currentPtr->getData() == x)
				return currentPtr;
			else
				currentPtr = currentPtr->getNext();
		return NULL;
	}
	Node* itemAt(int position) {
		if (position < 0 || position >= numOfItems)
			return NULL;
		Node* currentPtr = getHead();
		for (int k = 0; k != position; k++)
			currentPtr = currentPtr->getNext();
		return currentPtr;
	}
	
	void remove(T a)
	{
		// no items
		if (numOfItems == 0) return;
		// head is the item
		if (head_ptr->getData() == a)
		{
			if (numOfItems == 1)
			{
				delete head_ptr;
				head_ptr = NULL;
				tail_ptr = NULL;
				numOfItems = 0;
				return;
			}
			Node* currPtr = head_ptr;
			head_ptr = head_ptr->getNext();
			delete currPtr;
			numOfItems--;
			return;
		}

		Node* prev = head_ptr;
		Node* curr = head_ptr->getNext();
		// item is in the middle
		while (curr != NULL) {
			if (curr->getData() == a)
			{
				if (curr == tail_ptr)
				{
					prev->setNext(NULL);
					delete tail_ptr;
					tail_ptr = prev;
					numOfItems--;
					break;
				}
				prev->setNext(curr->getNext());
				delete curr;
				numOfItems--;
				break;
			}
			else
			{
				prev = curr;
				curr = curr->getNext();
				if (curr == tail_ptr)
				{
					prev->setNext(NULL);
					delete tail_ptr;
					tail_ptr = prev;
					numOfItems--;
					break;
				}
			}
		}
	}

	void insertHead(T x) { 
		Node* newHead = new Node(x, head_ptr);
		head_ptr = newHead;
		if (tail_ptr == NULL)
			tail_ptr = head_ptr;
		numOfItems++;
	}
	void insertTail(T x) {
		if (isEmpty())
			insertHead(x);
		else {
			Node* newTail = new Node(x);
			tail_ptr->setNext(newTail);
			tail_ptr = newTail;
			numOfItems++;
		}
	}
	void insert(Node* p, T x) {
		Node* currentPtr = head_ptr;
		while (currentPtr != NULL && currentPtr != p)
			currentPtr = currentPtr->getNext();
		if (currentPtr) {
			Node* newNode = new Node(x, p->getNext());
			p->setNext(newNode);
			numOfItems++;
		}
	} // sth in the middle

private:
	Node* head_ptr; Node* tail_ptr;
	int numOfItems;
};
