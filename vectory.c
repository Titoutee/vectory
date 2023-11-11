#include "stdio.h"
#include "vectory.h"
#include <stddef.h>


// Mutating operations
void push_end(Vec *vec, void *val) {
    
}
void push_front(Vec *vec, void *val);
void *pop_end(Vec *vec);
void *pop_front(Vec *vec);
void assign(Vec *vec);
void insert(Vec *vec, void *val, size_t idx);

// Infos
size_t len(Vec *vec);
size_t capacity(Vec *vec);
char is_initialised(Vec *vec);

// Building
void init(Vec *vec, size_t capacity); // Overrides the initializer constant

// Side-building
void from_array(Vec *vec, void *arr);
void from_bytes(Vec *vec, char arr[]);
void deep_copy(Vec *vec, Vec *other);
