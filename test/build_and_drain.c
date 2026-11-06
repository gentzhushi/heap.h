#include <stdio.h>

#define HEAP_H_IMPLEMENTATION_
#include "../heap.h"

const int inputs[] = { 1, 0, 3, 2, 4, 9, 8, 5, 6, 7 };

#define INPUT_COUNT (sizeof(inputs)/sizeof(inputs[0]))

int main(void)
{
	printf("=== TEST STARTED ===\n");

	struct heap h;
	heapinit(&h, 10);

	printf("Inserting: [ ");
	for (size_t i = 0; i < INPUT_COUNT; i++) {
		int val = inputs[i];
		heapput(&h, val);
		printf("%d ", val);
	}
	printf("]\n");

	printf("Removed:   [ ");
	int out = 0;
	while (heappop(&h, &out) >= 0) {
		printf("%d ", out);
	}
	printf("]\n");

	heapdel(&h);

	printf("=== TEST DONE ===\n");

	return 0;
}
