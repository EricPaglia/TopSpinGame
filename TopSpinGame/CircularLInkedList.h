#pragma once
#include <assert.h>
#include <iostream>
template <class T>
class LinkedList   //singly-linked 
{
public:
	class Node { // singly-linked nodes (basic containers of a linked list)  
	public:
		Node(T val, Node * nx = nullptr, Node *pv = nullptr) : value(val), next(nx), prev(pv) { } //initialization list 
		T  value;
		Node * next;
		Node * prev; //for doubly 
	};

public:
	LinkedList(); // construct an empty linked list
	LinkedList(const LinkedList &other);//copy constructor

	~LinkedList();     // destroy a linked list
	unsigned int size() const;  // return number of items in the list
	bool isEmpty() const; // true if list is empty, false otherwise
	void addHead(T item);  // adds item to front of list
	T removeHead();  // remove front node, and return the data T found in it;
					 // PRECONDITION: list must not be empty already
	T retrieveHead() const; // returns the data T in front node; 
							// PRECONDITION: list must not be empty already
	void addTail(T item); // add item to end of list
	T removeTail(); // remove last node, and return the data T found in it;
					// PRECONDITION: list must not be empty already
	T retrieveTail() const; // return data T in last node; 
							// PRECONDITION: list must not be empty already
	void add(unsigned int n, T item); // Add a new node containing an item in position n on the list
									  // PRECONDITION: n must be a valid list position (1<=n<=(size+1))
	T replace(unsigned int n, T item); // Replace the data stored in position n of the list with
									   // item, and return the replaced item; 
									   // PRECONDITION: n must be a valid list position (1<=n<=size)  
	T remove(unsigned int n); // Remove the node at position n from the list, and return the
							  // item it contained; PRECONDITION: n must be a valid list position (1<=n<=size)
	T retrieve(unsigned int n) const; // Return the item value from the node in position n; 
									  // PRECONDITION: n must be a valid list position (1<=n<=size)

									  // WARNING: ONLY FOR TESTING IN LAB 8 !!!
									  // The function below gives direct access to the Nodes 
									  // Once a user gets direct access to list nodes,
									  // internal list structure (e.g. linking) can be messed up.

	T retrieveNode(unsigned int n) const;
	//FOR TESTING ONLY

	void ShiftRight();
	void ShiftLeft();
	void ReverseList(int _index);
	void swap(int start, int end, int n); //n is the number of nodes that need to be reversed

	inline Node* getHead() const { return m_head; }

private:
	Node * m_head;
	Node * m_tail;
	unsigned int m_size;

public:
	class Iterator {// iterators are used for efficient traversal of linked lists
	private:
		Node* m_ptr;    // an iterator hides a pointer to node
	public:
		Iterator(Node* ptr) { m_ptr = ptr; }
		void operator++ () { m_ptr = m_ptr->next; } // for forward traversing, e,g, Iterator i=begin(); ... ++i;
		void operator-- () { m_ptr = m_ptr->prev; } // for reverse traversing 
		bool operator != (const Iterator& b) { return m_ptr != b.m_ptr; }
		T operator *() { return m_ptr->value; }
		T getValue() { return m_ptr->value; }
		//T setValue(int n) { m_ptr->value = n; }
		void setValue(T val) { m_ptr->value = val; }
	};

	// linked list objects create forward-traversal iterators using the functions below
	Iterator begin() const{ return Iterator(m_head); }
	Iterator end() { return Iterator(nullptr); }	
	Iterator last() { return Iterator(m_tail); } //for backwards traversal
};
// An implementation of templated class "LinkedList"


template <class T>
LinkedList<T> ::LinkedList() //Initialization list instead of constructor 
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{}

// a quickly made copy constructor
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {

	if (other.m_size == 0) { 
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
	else { //if list is not empty
		m_size = other.m_size;
		m_head = new Node(other.m_head->value, nullptr); //Creates a copy of the head using different pointer 
		if (other.m_tail == nullptr) {//only 1 item 
			m_tail = m_head;
		}
		else //more than 1 item
		{
			Node * copyFrom = other.m_head->next;
			Node *nextNode = m_head; //the new list 
			Node *prevNode = m_head; //prev points to head because right, there is only 1 node

			while (copyFrom != other.m_head) {
				nextNode->next = new Node(copyFrom->value);
				copyFrom = copyFrom->next;
				nextNode = nextNode->next; //nextNode will end pointing to tail
				if (nextNode != m_head)//doubly linking all the nodes with new pointers
				{
					nextNode->prev = prevNode;
					prevNode = prevNode->next;
				}
			}
			m_tail = nextNode;
		}

		//Make it circular
		m_head->prev = m_tail; //head points back to tail
		m_tail->next = m_head; //tail points back to head 

	}
}





template <class T>
LinkedList<T> :: ~LinkedList()
{
	Node * here = m_head, *nextNode;
	do
	{
		nextNode = here->next;

		delete here; //DESTRUCTOR IS CAUSING PROBLEM 
					 //Aftter deleting all the nodes, goes through loop 1 more time tries to delete nothing causing the program to crash
					 //std::cout << "Node Deleted\n";
		here = nextNode;
	} while ((here) != m_head);

}

template <class T>
unsigned int LinkedList<T> ::size() const
{
	return m_size;
}

template <class T>
bool LinkedList<T> ::isEmpty() const
{
	return (m_size == 0);
}

template <class T>
void LinkedList<T> ::addHead(T item)
{
	Node * OldHead = m_head;
	m_head = new Node(item, m_head, m_tail); //3rd parameter points to tail
											 //m_head->prev = m_tail;

	if (m_tail == nullptr)
		m_tail = m_head;
	else
	{
		OldHead->prev = m_head;
		m_tail->next = m_head; //tail points to head 
	}

	m_size++;
}

template <class T>
T LinkedList<T> ::removeHead()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeHead)")); //If it's empty, then exit the function 
	Node * oldNode = m_head;
	T returnVal = m_head->value;
	m_head = m_head->next; //make the following node the new head
	m_head->prev = m_tail; //link new had back to tail
	m_tail->next = m_head; //link tail back to new head 
	if (m_head == nullptr) m_tail = nullptr;
	m_size--;
	delete oldNode;
	return returnVal;
}

template <class T>
T LinkedList<T>::retrieveHead() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveHead)"));
	return m_head->value;
}

template <class T>
void LinkedList<T> ::addTail(T item)
{
	if (isEmpty()) addHead(item);
	else
	{
		Node *originalTail = m_tail; //store original tail
		m_tail = m_tail->next = new Node(item);
		m_tail->prev = originalTail;

		m_tail->next = m_head; //point back to the head to make it circular
		m_head->prev = m_tail;  //Point head back to new tail

		m_size++;
	}
}

template <class T>
T LinkedList<T> ::removeTail()
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in removeTail)"));
	if (m_head == m_tail) return removeHead();
	T returnVal = m_tail->value;
	m_tail->prev = nullptr;
	Node * preTail = m_head;
	while (preTail->next != m_tail)
		preTail = preTail->next;
	preTail->next = m_head; //Connect new tail to head
	m_head->prev = preTail; //Connect head to new tail

							//m_tail->prev = preTail->next; //for doubly --> //for circular, replace nullPtr with m_head
							//Not necessary

							//m_tail->next = m_head; //For Circular

	delete m_tail;
	m_tail = preTail;
	m_size--;
	return returnVal;
}

template <class T>
T LinkedList<T> ::retrieveTail() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "LinkedList is Empty (in retrieveTail)"));
	return m_tail->value;
}

template <class T>
void LinkedList<T> ::add(unsigned int n, T item) //DOESN'T WORK
{
	// PRECONDITION: n should be a valid position in the list
	assert(((n >= 1) && (n <= size() + 1) && "LinkedList index is out of bounds (in add)"));
	if (n == 1)          addHead(item);
	else if (n == (size() + 1)) addTail(item);
	else
	{
		Node * here = m_head;
		//Node * previous = m_head;
		for (unsigned int k = 1; k < n - 1; k++)
		{
			here = here->next;
			//previous = here;
		}

		here->next = new Node(item, here->next, here);
		here->next->next->prev = here->next; //here->next is the node you are adding...
											 //here->next->next is the following node
											 //take following node->prev and equate it to the node you are adding (which is here->next)
		m_size++;
	}
}

template <class T>
T LinkedList<T> ::replace(unsigned int n, T item)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in replace)"));
	T returnValue;
	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++)
		here = here->next;
	returnValue = here->value;
	here->value = item;
	return returnValue;
}

template <class T>
T LinkedList<T> ::remove(unsigned int n)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in remove)"));
	if (n == 1) return removeHead();
	if (n == size()) return removeTail();

	Node * here = m_head;
	for (unsigned int k = 1; k < n - 1; k++)
		here = here->next; //the node before the node you want to remove 
	Node * kill = here->next;
	T returnVal = kill->value;
	here->next = kill->next; //Linking nodes

	(kill->next)->prev = here; //can't be equal to here->next because that is equal to itself
							   //This causes a break in the chain

	delete kill;
	m_size--;
	return returnVal;
}

template <class T>
T LinkedList<T> ::retrieve(unsigned int n) const
{
	// PRECONDITION: n must be a valid current list position
	//std::cout << "The Value of n: " << n << "\n";
	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in retrieve)"));
	if (n == 1) return retrieveHead();
	if (n == size()) return retrieveTail();
	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++) here = here->next;
	return here->value;
}

//FOR TESTING ONLY
//template <class T>
//T LinkedList<T> ::retrieveNode(unsigned int n) 
//{
//	// PRECONDITION: n must be a valid current list position
//	assert(((n >= 1) && (n <= size()) && "LinkedList index is out of bounds (in retrieve)"));
//	if (n == 1) return m_head();
//	//if (n == size()) return retrieveTail();
//	Node * here = m_head;
//	for (unsigned int k = 1; k < n; k++) here = here->next;
//	return here;
//}

template <class T>
void LinkedList<T>::ShiftRight()
{

	//Node *previous = m_tail;
	Node *here = m_head;


	for (int i = 0; i <= m_size; i++)
	{
		//m_head->prev = m_tail;
		here = here->next;

	}
	//m_head->next = m_head->next->next;
	m_head = m_head->prev;

}

template <class T>
void LinkedList<T>::ShiftLeft() 
{
	//Shifted all the pointers by one 

	//Node *previous = m_tail;
	Node *here = m_head;


	for (int i = 0; i <= m_size; i++)
	{
		//m_head->prev = m_tail;
		here = here->prev;

	}
	//m_head->next = m_head->next->next;
	m_head = m_head->next;
}

template <class T>
void LinkedList<T>::ReverseList(int _index)
{
	int temp;
	int size = _index;


	if (_index % 2 != 0) //If number is odd, perform one less swap to avoid swapping the same number in the end
	{
		for (int i = 0; i < (size / 2) - 1; i++) //
		{
			temp = index[i];//store first variable as temp
			index[i] = index[size - i - 1]; //replace first position with last position
			index[size - i - 1] = temp; //replace last position with first position using the value stored in temp
		}
	}
	else
	{
		for (int i = 0; i < size / 2; i++) //
		{
			temp = index[i];//store first variable as temp
			index[i] = index[size - i - 1]; //replace first position with last position
			index[size - i - 1] = temp; //replace last position with first position using the value stored in temp
		}
	}
}

template <class T> 
void LinkedList<T> :: swap(int start, int end, int n)
{
	
	Node *begin = m_head;
	Node *current = m_head_next;

	for (int i = 0; i < start; i++)
	{
		begin = begin->next; //start point 
		current = current->next; //The node you are moving 
	}
	Node *temp;
	for (int i = 0; i < n; i++)
	{
		current->next = begin; //Make the current node point to the starting node
		begin->prev = current; //make the starting node point to the node that was just moved

		temp = current; //temporarily store the position of the node you just moved
		curent = begin->next; //make current point to the next node you are moving 
		begin = temp; //Let the node you just moved be the start point

	}
		
}
/*{

	int n = end - start; 
	Node *start = m_head;
	Node *end = m_head;
	Node *here = m_head->next;
	for (int i = 0; i < start; i++)
	{
		start = here->next;
		end = end->next;
		here = here->next; 
	}
	for (int i = start; i < end; i++)
	{
		end = end->next;
	}

	for (int i = 0; i < n; i++)
	{
		here->next = start;
		start->prev = here;
	}
	

}*/