#ifndef HEAP_H_
#define HEAP_H_

#include <stddef.h>
#include <sys/types.h>

typedef struct heap {
	int *items;
	int count;
	int capacity;
} heap_t;

int heapinit(struct heap *h, int initcap);
int heapdel(struct heap *h);
int heappop(struct heap *h, int *out);
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
static int heap__child_idx_if_larger(struct heap *h, int target_idx)
{
	int max_idx = -1;

	// Left child
	int left_idx = target_idx * 2 + 1;
	if (left_idx >= h->count)
		// This means the left child isn't present. Due to our
		// implementation details, this makes the presence of a right
		// child to be impossible as well.
		return -1;

	int left = h->items[left_idx];
	if (left > h->items[target_idx])
		max_idx = left_idx;

	// Right child
	int right_idx = target_idx * 2 + 2;
	if (right_idx >= h->count)
		// If the right child isn't present, return either -1, or the
		// left child's id if its value was larger than the parent's
		return max_idx;

	int right = h->items[right_idx];
	if (right > h->items[target_idx] && right > left)
		max_idx = right_idx;

	return max_idx;
}

static int heap__parent_idx_if_smaller(struct heap *h, int target_idx)
{
	if (target_idx == 0)
		return -1;

	int parent_idx = target_idx / 2;
	if (target_idx % 2 == 0)
		// Decrement the index so the integer division trick works for
		// index access
		parent_idx = (target_idx - 1) / 2;


	if (h->items[parent_idx] >= h->items[target_idx])
		return -1; 

	return parent_idx;
}

// Create a new max heap
int heapinit(struct heap *h, int initcap)
{
	h->count    = 0;
	h->capacity = initcap;
	h->items    = malloc((uint)initcap * sizeof(int));
    return 0;
}

int heapdel(struct heap *h)
{
	free(h->items);
	return 0;
}

int heappop(struct heap *h, int *out)
{
	if (h->count == 0)
		return -1;

	int output = h->items[0];

	h->items[0] = h->items[--h->count];

	int target_idx = 0;

	// Get the children, let them be A and B. While target (which is
	// `items[target_idx]`) has a child or children larger than it, replace
	// it with the larget one.
	
	int idx;

	while ((idx = heap__child_idx_if_larger(h, target_idx)) >= 0) {
		heap__swap(&h->items[target_idx], &h->items[idx]);
		target_idx = idx;
	}

	*out = output;
	return 0;
}

int heapput(struct heap *h, int val)
{
	if (h->count >= h->capacity) {
		h->capacity *= 2;
		void* tmp = realloc(h->items, (uint)h->count * sizeof(int));

		if (!tmp)
			return -1;

		h->items = tmp;
	}

	int target_idx = h->count++;

	h->items[target_idx] = val;
	
	int idx;
	while ((idx = heap__parent_idx_if_smaller(h, target_idx)) >= 0) {
		heap__swap(&h->items[target_idx], &h->items[idx]);
		target_idx = idx;
	}

	return 0;
}

#endif // !HEAP_H_IMPLEMENTATION_
