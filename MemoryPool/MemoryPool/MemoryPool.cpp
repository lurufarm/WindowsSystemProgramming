#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class MemoryPool
{
public:
	MemoryPool(int byte)
	{
		mSz = byte;
		mIndex = 0;
		for (size_t i = 0; i < mSz; i++)
		{
			mPool.push_back(0);
		}
	}
	~MemoryPool()
	{
	}

	char* allocate(int szof)
	{
		char* result = &mPool[mIndex];
		mIndex += szof;
		return result;
	}

	template <typename T>
	void deallocate(T* data)
	{
		for (size_t i = 0; i < mSz; i++)
		{
			if (&mPool[i] == reinterpret_cast<char*>(data))
			{
				for (size_t j = 0; j < sizeof(data); j++)
				{
					*data = 0;
				}
				return;
			}
		}
	}

	void Resize(int num)
	{
		int sz = num + mSz;
		for (size_t i = mSz; i < sz; i++)
		{
			mPool.push_back((char)i);
		}
		mSz += num;
	}
	
	bool IsFull()
	{
		if (mIndex < mSz)
			return false;
		else if (mIndex == mSz)
			return true;
	}

	char* GetPoolAddress()
	{
		return &mPool[0];
	}

private:
	vector<char> mPool;
	int mSz;
	int mIndex;
};

class Object
{
#pragma region class Object
public:
	enum class ObjState
	{
		Paused,
		Active
	};
	Object()
	{
		mActive = false;
		mUsable = true;
	}
	virtual void Initialize()
	{
		mActive = true;
		mUsable = false;
	}
	// Update ....

	bool mActive;
	bool mUsable;
#pragma endregion
};

class objectPool
{
public:
	objectPool(int sz, int szof)
		: mIndex(0)
	{
		mSz = sz;
		mSzof = szof;
		mMp = new MemoryPool(sz * szof);
	}
	~objectPool()
	{
		mMp->deallocate(mMp);
	}

	template <typename T, typename... Pr>
	Object* MakeObject(Pr... param)
	{
		if (mMp->IsFull())
			return nullptr;

		T* obj = new (mMp->allocate(sizeof(T))) T(param...);
		Object* object = dynamic_cast<Object*>(obj);
		if (!object)
			return nullptr;
		
		mOPool.push_back(object);
		return object;
	}

	void ObjActivating(int num)
	{
		if (mIndex + num >= mSz)
			return;

		int index = mIndex + num;

		for (size_t i = mIndex; i < index; i++)
		{
			if (mOPool[i]->mUsable)
			{
				mOPool[i]->Initialize();
			}
			else
			{
				index++;
			}
		}

		mIndex += num;
	}

	template <typename T>
	T* GetObject(int index)
	{
		if (index > mSz)
			return nullptr;

		T* result = dynamic_cast<T*>(mOPool[index]);
		return result;
	}

	MemoryPool* GetMemoryPool()
	{
		return mMp;
	}

private:
	vector<Object*>mOPool;
	MemoryPool* mMp;
	int mSz;
	int mSzof;
	int mIndex;
	
};

class Monster : public Object
{
public:
	Monster()
		: mStat_HP(10)
		, mStat_Strength(10)
	{
	}
	void Initialize()
	{
		mStat_HP = 10;
		mStat_Strength = 10;
		// ...
	}
	void Update()
	{
		if (mStat_HP <= 0)
			mActive = false;
		// ...
	}
	int mStat_HP;
	int mStat_Strength;
private:
};


int main()
{
	int sz1 = sizeof(Monster);
	int sz2 = sizeof(Object);

	objectPool* monsterpool = new objectPool(3, sz1);
	char* poolAdrs = monsterpool->GetMemoryPool()->GetPoolAddress();

	monsterpool->MakeObject<Monster>();
	monsterpool->MakeObject<Monster>();
	monsterpool->MakeObject<Monster>();

	Monster* mob = monsterpool->GetObject<Monster>(0);

	return 0;
}