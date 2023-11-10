#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
	Node()
	{
		
	}
	T data;
	Node* next;
};

template <typename T>
class SLList
{
public:
	SLList()
	{
		sz = 0;
		head = nullptr;
		tail = nullptr;
	}
	void push_front(T data)
	{
		Node* newNode = new Node<T>();
		newNode->data = data;
		if (sz == 0)
		{
			head = newNode;
			head->next = nullptr;
			sz++;
			return;
		}

		newNode->next = head;
		head = newNode;
		sz++;
	}
	void push_back(T data)
	{

	}

	int sz;
	Node<T>* head;
	Node<T>* tail;
private:
};

int main()
{

}