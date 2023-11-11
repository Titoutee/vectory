#include "stdio.h"
#include "vectory.h"
#include <complex.h>
#include "memory.h"
#include <stddef.h>
#include <stdlib.h>
#include <strings.h>


// Mutating operations
int push_end(Vec *vec, void *val) {
    if (sizeof(*val) != vec->elt_size) { //The pushed element should have the valid type (vec initialisation)
        return VEC_FAILURE;
    }

    // Checks for capacity validity and realloc in consequence
    if (!_valid_capacity(vec)) {
        _realloc(vec);
    }

    memcpy(&vec->data[vec->len], val, vec->elt_size);
    vec->len++;
    
    return VEC_SUCCESS;
}

void _realloc(Vec *vec) {
    vec->capacity *= 2; // Common factor with good (allocating cost/freq. of reallocation) balance
    void *_grbg = realloc(vec->data, vec->elt_size*vec->capacity);
}   
void push_front(Vec *vec, void *val);
void pop_end(Vec *vec, void *buffer) {

}
void *pop_front(Vec *vec);
void assign(Vec *vec);
void insert(Vec *vec, void *val, size_t idx);

// Infos
size_t len(Vec *vec) {
    return vec->len;
}
size_t capacity(Vec *vec) {
    return vec->capacity;
}
char is_initialised(Vec *vec) {
    return (vec->data == NULL) ? 0 : 1;
}

inline char _valid_capacity(Vec *vec) {
    return (vec->len == vec->capacity) ? 0 : 1;
}

// Building
char init(Vec *vec, size_t capacity, size_t elt_size) {
    vec->capacity = capacity;
    vec->len = 0;
    vec->elt_size = elt_size;
    vec->data = malloc(capacity*elt_size);

    return (vec->data == NULL) ? VEC_FAILURE : VEC_SUCCESS;
}

// Side-building
void from_array(Vec *vec, void *arr);
void from_bytes(Vec *vec, char arr[]);
void deep_copy(Vec *vec, Vec *other);
