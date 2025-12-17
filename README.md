# DSA Visual Library

A visual learning library for Data Structures and Algorithms in C with colorful terminal output.

## What's Included

**Data Structures:** Linked List, Stack, Queue, Binary Tree, Graph

**Sorting:** Bubble, Selection, Insertion, Quick, Merge

**Searching:** Linear, Binary

## Build & Run

```bash
make
./dsa_demo
```

Or compile manually:
```bash
gcc -Wall -std=c11 -o dsa_demo src/*.c
```

## Usage

Run `./dsa_demo` and pick from the menu. Each demo shows step-by-step visualization with colored output.

You can also use it as a library:

```c
#include "dsa_visual.h"

int main() {
    LinkedList* list = ll_create();
    ll_insert_back(list, 10);
    ll_visualize(list);
    ll_free(list);
    return 0;
}
```

## Notes

- Needs a terminal that supports ANSI colors (most do)
- Animations can be sped up by changing `usleep()` values in source

## License

MIT
