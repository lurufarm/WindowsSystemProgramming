#include <vector>

template <typename T>
class MemoryPool
{
public:
	MemoryPool(int size, int sof)
		: mSize(size)
		, mSizeof(sof)
		, mIndex(0)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			T* t = new T[mSizeof];
			mPool.push_back(t);
		}
	}

	~MemoryPool()
	{
		for (T* memory : mPool)
		{
			delete[] memory;
		}
	}

	T* allocate()
	{
		return mPool[mIndex++];
	}

	void deallocate(T* data)
	{
		for (size_t i = 0; i < mPool.size(); i++)
		{
			if (data == mPool[i])
			{
				*mPool[i] = NULL;
				break;
			}
		}
		mIndex--;
	}

	void clear()
	{
		for (size_t i = 0; i < mPool.size(); i++)
		{
			*mPool[i] = NULL;
		}
	}

	bool IsEmpty()
	{
		for (size_t i = 0; i < mPool.size(); i++)
		{
			if (*mPool[i] != NULL)
				return false;
		}
		return true;
	}
	bool IsFull()
	{
		for (T* data : mPool)
		{
			if (*data == NULL)
				return false;
		}
		return true;
	}
	void Resize(int num)
	{
		for (size_t i = mSize; i < num; i++)
		{
			T* t = new T[mSizeof];
			mPool.push_back(t);
		}
		mSize = num;
	}

private:
	int mSize;
	int mSizeof;
	int mIndex;
	std::vector<T*> mPool;
};

int main()
{
	MemoryPool<int> mp(100000, sizeof(int));

	int* a = mp.allocate();
	*a = 100;

	mp.deallocate(a);

	return 0;
}

