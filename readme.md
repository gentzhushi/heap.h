# `heap.h`

An STB-style library for the heap data structure in C.

## How to use in you project

You already know the drill. Copy-paste it in you project, include it, and `#define HEAP_H_IMPLEMENTATION_`:

```c
#define HEAP_H_IMPLEMENTATION_
#include "path/to/heap.h"

int main(void)
{
        struct heap *h;

        int cap = 21;
        heapinit(&h, cap);

        int val = 1337;
        heapput(&h, val);

        int out;
        heappop(&h, *out);

        heapdel(&h);
}
```

That's about it.
