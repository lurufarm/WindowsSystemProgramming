#include <iostream>

template <typename T>
class Stack
{
public:
	Stack(int size)
		: mSize(size)
		, mPoint(0)
	{
		mArray = new T[mSize];
	}
	~Stack()
	{
		this->clear();
		delete[] mArray;
	}

	void push(T data)
	{
		if (mSize <= mPoint)
			return;
		
		mArray[mPoint++] = data;
	}

	T pop()
	{
		if (mPoint == 0)
			return T();

		return mArray[--mPoint];
	}

	void clear()
	{
		for (size_t i = 0; i < mPoint; i++)
		{
			mArray[mPoint] = NULL;
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
		return mUsing == 0;
	}

private:
	int mSize;
	int mPoint;
	T* mArray;
};

int main()
{

	return 0;
}