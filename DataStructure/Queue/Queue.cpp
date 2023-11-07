// Queue.cpp
#include <iostream>

template <typename T>
class Queue
{
public:
	Queue(int size)
		: mSize(size)
		, mPoint(0)
	{
		mArray = new T [mSize];
	}
	~Queue()
	{
		this->clear();
		delete[] mArray;
	}

	void push(T data)
	{
		if (mPoint >= mSize)
			return;
		mArray[mPoint++] = data;
	}

	T pop()
	{
		if (mPoint == 0)
			return T();

		T result = mArray[0];
		for (size_t i = 0; i < mPoint - 1; i++)
		{
			mArray[i] = mArray[i + 1];	
		}
		mPoint--;
		return result;
	}

	void clear()
	{
		for (size_t i = 0; i < mArray[mPoint]; i++)
		{
			mArray[i] = NULL;
		}
		mPoint = 0;
	}

	int find(T data)
	{
		for (size_t i = 0; i < mPoint; i++)
		{
			if (mArray[i] == data)
				return i;
		}
		return T();
	}

	int size()
	{
		return mPoint;
	}

	bool IsEmpty()
	{
		return mPoint == 0;
	}

private:
	int mSize;
	int mPoint;
	T* mArray;
};

int main()
{
	Queue<int>* queue = new Queue<int>(10);

	queue->push(10);
	queue->push(20);
	queue->push(30);

	for (size_t i = 0; i < 3; i++)
	{
		int answer = queue->find(10 * i + 10);
		printf("%d\n", answer);
	}

}
