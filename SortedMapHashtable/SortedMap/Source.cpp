#include "SortedMap.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

bool rel(TKey cheie1, TKey cheie2) {
	if (cheie1 < cheie2) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	testAll();
	testAllExtended();
	//mytest();
}

void mytest()
{
	int** p = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		p[i] = nullptr;
	}

	p[0] = new int;
	*p[0] = 10;

	SortedMap m(rel);
	m.add(24, 1);
	m.add(11, 1);
	m.add(37, 1);
	m.add(2, 1);
	m.add(3, 1);
	m.add(8, 1);
	m.add(22, 1);
	m.add(15, 1);
	m.add(16, 1);
	m.add(28, 1);

	m.print();
}