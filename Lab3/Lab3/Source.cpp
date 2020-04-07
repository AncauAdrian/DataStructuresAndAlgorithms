#define _CRTDBG_MAP_ALLOC
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>


int main()
{
	testAll();
	testAllExtended();
	_CrtDumpMemoryLeaks();

	return 0;
}