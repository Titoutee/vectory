#include "../vectory.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int a = 5;
  int *b = &a;
  assert(sizeof(a) == sizeof(*b));

  Vec vec;
  if (init(&vec, CAP_DEF, sizeof(int)) == VEC_FAILURE) {
    fprintf(stderr, "Unrecoverable error while initialiazing vector...\n");
    exit(EXIT_FAILURE);
  }

  format(&vec);

  int val = 5;
  if (push_end(&vec, (int *)&val) == VEC_FAILURE) {
    fprintf(stderr, "Incompatible type in vector insertion...\n");
    exit(EXIT_FAILURE);
  }

  format(&vec);

  __realloc(&vec);
  
  format(&vec);
  // Vec v = VEC_VOID;
  return 0;
}