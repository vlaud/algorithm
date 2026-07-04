#include <iostream>
using namespace std;

class BitMaskFilter
{
public:
	// 생성자
	BitMaskFilter(int* inputData, int dataSize) : mData(inputData), mSize(dataSize)
	{
		mMask = 0xffffffff;
		if (mSize < 32)
		{
			mMask = (1u << mSize) - 1;
		}
	}
	~BitMaskFilter() {}

	void SetBit(int index, bool value)
	{
		if (index >= 0 && index < mSize && index < 32)
		{
			if (value) mMask |= (1u << index);
			else mMask &= ~(1u << index);
				
		}
	}

	bool GetBit(int index)
	{
		if (index >= 0 && index < mSize && index < 32)
		{
			return (mMask & (1u << index)) != 0;
		}
		return false;
	}

	void SetMask(unsigned int newMask)
	{
		mMask = newMask;
	}

	int ApplyFilter(int* result)
	{
		int resultIndex = 0;
		for (int i = 0; i < mSize && i < 32; i++)
		{
			if (mMask & (1u << i)) // i번째 비트 1인지 확인
			{
				result[resultIndex++] = mData[i];

			}
		}
		return resultIndex;
	}

	void PrintMask()
	{
		cout << "Mask (binary): ";
		for (int i = mSize - 1; i >= 0; i--)
		{
			cout << ((mMask & (1u << i)) ? '1' : '0');
		}
		cout << " (0x";
		cout.flags(ios::hex);
		cout << mMask;
		cout.flags(ios::dec);
		cout << ")" << endl;
	}

	void SetAllBits()
	{
		mMask = (mSize < 32) ? (1u << mSize) - 1 : 0xffffffff;
	}

	void ClearAllBits()
	{
		mMask = 0;
	}

	void InvertMask()
	{
		mMask = ~mMask;
		if (mSize < 32)
		{
			mMask &= (1u << mSize) - 1;
		}
	}

	void IntersectWith(unsigned int otherMask)
	{
		mMask &= otherMask;
	}

	void UnionWith(unsigned int otherMask)
	{
		mMask |= otherMask;
	}

	int CountSetBits()
	{
		int count = 0;
		unsigned int temp = mMask;
		while (temp)
		{
			count += temp & 1;
			temp >>= 1;
		}
		return count;
	}
private:
	int *mData, mSize;
	unsigned int mMask;
};

void printfiltering(BitMaskFilter filter, int *result)
{
	filter.PrintMask();
	int count = filter.ApplyFilter(result);
	cout << "필터된 데이터: ";
	for (int i = 0; i < count; i++)
	{
		cout << result[i] << " ";
	}
	cout << endl << endl;
}

int main()
{
	int data[] = { 10,20,30,40,50,60,70,80 };
	int dataSize = 8;
	int result[8];

	BitMaskFilter filter(data, dataSize);

	cout << "=== 비트 마스킹 데이터 필터링 예제 ===" << endl << endl;

	// 초기 상태 (모든 데이터 포함)
	cout << "1. 초기 상태 (모든 데이터 포함):" << endl;
	filter.PrintMask();
	int count = filter.ApplyFilter(result);
	cout << "필터된 데이터: ";
	for (int i = 0; i < count; i++)
	{
		cout << result[i] << " ";
	}
	cout << endl << endl;

	cout << "2. 짝수 인덱스만 선택 (0, 2, 4, 6):" << endl;
	filter.ClearAllBits();
	filter.SetBit(0, true);
	filter.SetBit(2, true);
	filter.SetBit(4, true);
	filter.SetBit(6, true);
	filter.PrintMask();
	count = filter.ApplyFilter(result);
	cout << "필터된 데이터: ";
	for (int i = 0; i < count; i++)
	{
		cout << result[i] << " ";
	}
	cout << endl << endl;

	cout << "3. 비트 연산으로 마스크 설정 (0b10110101):" << endl;
	filter.SetMask(0b10110101); // 0, 2, 4, 5, 7번째
	filter.PrintMask();
	cout << "필터된 데이터: ";
	count = filter.ApplyFilter(result);
	for (int i = 0; i < count; i++)
	{
		cout << result[i] << " ";
	}
	cout << "설정된 비트 개수: " << filter.CountSetBits() << endl << endl;

	cout << "4.마스크 반전:" << endl;
	filter.InvertMask();
	filter.PrintMask();
	count = filter.ApplyFilter(result);
	cout << "필터된 데이터: ";
	for (int i = 0; i < count; i++)
	{
		cout << result[i] << " ";
	}
	cout << endl << endl;

	cout << "5. 마스크 교집합 연산:" << endl;
	filter.SetMask(0b11110000);
	cout << "마스크 A: ";
	filter.PrintMask();

	unsigned int maskB = 0b10101010;
	cout << "마스크 B: ";
	for (int i = 7; i >= 0; i--)
	{
		cout << ((maskB & (1u << i)) ? '1' : '0');
	}
	cout << endl;

	filter.IntersectWith(maskB);
	cout << "교집합 결과: ";
	printfiltering(filter, result);
	return 0;
}
