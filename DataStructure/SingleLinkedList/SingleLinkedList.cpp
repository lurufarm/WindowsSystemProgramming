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
		Node<T>* newNode = push_process(data);
		newNode->next = head;
		head = newNode;
		sz++;
	}
	void insert(T data, int index)
	{
		if (index == 0)
		{
			push_front(data);
			return;
		}
		Node<T>* newNode = push_process(data);
		Node<T>* curNode = head;
		Node<T>* prevNode = head;
		int curIdx = 0;
		while (curIdx < index && curNode->next != nullptr)
		{
			curIdx++;
			prevNode = curNode;
			curNode = curNode->next;
		}
		if (curIdx < index)
		{
			cout << "Insert Failed" << endl;
			return;
		}
		prevNode->next = newNode;
		newNode->next = curNode;
		sz++;
	}
	void push_back(T data)
	{
		Node<T>* newNode = push_process(data);
		tail->next = newNode;
		tail = newNode;
		tail->next = nullptr;
		sz++;
	}
	T pop_front()
	{
		if (sz == 0)
		{
			return NULL;
		}
		T result = head->data;
		Node<T>* headNode = head;
		head = head->next;
		sz--;
		cout << result << " 가 pop_front 되었습니다" << endl;
		return result;
	}
	T pop_back()
	{
		if (sz == 0)
		{
			return NULL;
		}
		T result = tail->data;
		Node<T>* curNode = head;
		while (curNode->next->next != nullptr)
		{
			curNode = curNode->next;
		}

		curNode->next = nullptr;
		tail = curNode;
		sz--;
		cout << result << " 가 pop_back 되었습니다" << endl;
		return result;
	}

	void printlist_int()
	{
		Node<T>* headNode = head;
		while (nullptr != headNode)
		{
			cout << headNode->data << endl;
			headNode = headNode->next;
		}
	}

	int sz;
	Node<T>* head;
	Node<T>* tail;
private:
	Node<T>* push_process(T data)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = data;
		if (sz == 0)
			first_push(newNode);
		return newNode;
	}
	void first_push(Node<T>* newNode)
	{
		head = newNode;
		tail = newNode;
		head->next = tail;
		sz++;
		return;
	}
};

int main()
{
	SLList<int>* sllist = new SLList<int>();
	for (int i = 0; i < 10; i++)
	{
		sllist->push_front(i);
	}
	for (int i = 10; i < 20; i++)
	{
		sllist->push_back(i);
	}
	cout << "push 결과" << endl;
	sllist->printlist_int();

	for (int i = 99; i > 98; i--)
	{
		sllist->insert(i, 0);
	}
	
	cout << "insert 결과" << endl;
	sllist->printlist_int();

	return 0;
}