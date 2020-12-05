#ifndef _VM_INCLUDE_RANDOM_H
#define _VM_INCLUDE_RANDOM_H

#include <stdint.h>

uint64_t next (void);

/* This is the jump function for the generator. It is equivalent
   to 2^64 calls to next(); it can be used to generate 2^64
   non-overlapping subsequences for parallel computations. */
void jump (void);

/* This is the long-jump function for the generator. It is equivalent to
   2^96 calls to next(); it can be used to generate 2^32 starting points,
   from each of which jump() will generate 2^32 non-overlapping
   subsequences for parallel distributed computations. */
void long_jump (void);

#endif /* _VM_INCLUDE_RANDOM_H */
