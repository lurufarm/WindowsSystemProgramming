#include <iostream>
#include <stack>

using namespace std;

class MemoryPool
{
public:
	MemoryPool(int spaceByte)
	{
		mSz = spaceByte;
		for (size_t i = 0; i < mSz; i++)
		{
			mPool.push(0);
		}
	}
	virtual ~MemoryPool();

	char* allocate(int szof)
	{
		char* result = &mPool.
	}
	

private:
	stack<char> mPool;
	int mSz;
};


int main()
{

}