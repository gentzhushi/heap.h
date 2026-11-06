#ifndef HEAP_H_
#define HEAP_H_

#include <stddef.h>

typedef struct heap {
	int *items;
	size_t count;
	size_t capacity;
} heap_t;

int heapinit(struct heap *hsize_t initcap);
int heapdel(struct heap *h);
int heappop(struct heap *h);
int heapput(struct heap *h, int val);

#endif // !HEAP_H_

#ifndef HEAP_H_IMPLEMENTATION_

#include <stdlib.h>

// For reference, here's a mirror of a tree based off of an array with 15
// values (the numbers symbolize indicies).
//
//               00
//            /      \
//           /        \
//       01              02
//      /  \            /  \
//   03      04      05      06
//   /\      /\      /\      /\
// 07  08  09  10  11  12  13  14

static inline void heap__swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// Find the children of the node @ `h->items[target_idx]` and compare their
// values to their parent. If one or both are larger, return the larger child;
// else return -1.
static ssize_t heap__child_idx_if_larger(struct heap *h, size_t target_idx)
{
	int left  = h->items[(target_idx)     * 2 - 1];
	int right = h->items[(target_idx + 1) * 2];
	int parent = h->items[target_idx]

	if (left < parent && right < parent)
		return -1;

	a >= b ? return a : return b;
}

static ssize_t heap__parent_idx_if_smaller(struct heap *h, size_t target_idx)
{
	if (target_idx == 0)
		return -1;

	int parent_idx = target_idx / 2;

	if (h->items[parent_idx] >= h->items[target_idx])
		return -1; 

	return parent_idx
}

// Create a new max heap
int heapinit(struct heap *h, size_t initcap);
{
	h->count    = 0,
	h->capacity = initcap,
	h->items    = malloc(initcap * sizeof(int)),
	return h;
}

void heapdel(struct heap *h)
{
	free(h->items);
}

int heappop(struct heap *h)
{
	int output = h->items[0];

	h->items[0] = h->items[--h->count];

	int target_idx = 0;

	// Get the children, let them be A and B. While target (which is
	// `items[target_idx]`) has a child or children larger than it, replace
	// it with the larget one.
	
	int idx;

	while ((idx = _heap_child_idx_if_larger(h, target_idx)) > 0) {
		heap__swap(&h->items[target_idx], &h->items[idx]);
		target_idx = idx;
	}

	*out = output;
	return 0;
}

int heapput(struct heap *h, int val)
{
	if (h->capacity >= h->count) {
		h->capacity *= 2;
		void* tmp = realloc(h->items, sizeof(int));

		if (!tmp)
			return -1;

		h->items = tmp;
	}

	ssize_t target_idx = h->count++;

	h->items[target_idx] = val;
	
	int idx;
	while ((idx = _heap_parent_idx_if_smaller(h, target_idx)) > 0) {
		heap__swap(&h->items[target_idx], &h->items[idx]);
		target_idx = idx;
	}

	return 0;
}

#endif // !HEAP_H_IMPLEMENTATION_
