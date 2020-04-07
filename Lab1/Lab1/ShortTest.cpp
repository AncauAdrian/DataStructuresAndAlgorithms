#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "Iterator.h"
#include <iostream>


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5); // 8
	b.add(1); // 4
	b.add(10); // 13
	b.add(7); // 10
	b.add(1); // 4
	b.add(11); // 14
	b.add(-3); // 0
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	assert(b.elementsWithMinimumFrequency() == 6);
	b.add(5);
	b.add(10);
	assert(b.elementsWithMinimumFrequency() == 4);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		//std::cout << e << std::endl;
		it.next();
	}
}
