#include "../vectory.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int a = 5;
  int *b = &a;
  assert(sizeof(a) == sizeof(*b)); // Junk

  // Initialisation testing
  Vec vec;
  if (init(&vec, CAP_DEF, sizeof(int)) == VEC_FAILURE) {
    fprintf(stderr, "Unrecoverable error while initialiazing vector...\n");
    exit(EXIT_FAILURE);
  }

  // Format testing
  format(&vec);
  
  // Push to end testing
  int val = 2;
  if (push_end(&vec, (int *)&val) == VEC_FAILURE) {
    fprintf(stderr, "Incompatible type in vector insertion...\n");
    exit(EXIT_FAILURE);
  }

  format(&vec);
  push_end(&vec, &val);
  push_end(&vec, &val);
  format(&vec);
  int *elt = at(&vec, 0);
  assert(*elt == (int)2);
  
  shrink_to_fit(&vec);

  

  format(&vec);


  return 0;
}