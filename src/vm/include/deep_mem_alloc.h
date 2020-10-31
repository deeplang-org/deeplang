#ifndef _DEEP_MEM_ALLOC_H
#define _DEEP_MEM_ALLOC_H

#include "bh_platform.h"

#define FAST_BIN_LENGTH (8)
#define FAST_BIN_MAX_SIZE (64) /* 8 * 8 bytes */

#define A_FLAG_OFFSET (0) /* allocated */
#define A_FLAG_MASK (0x00000001)
#define P_FLAG_OFFSET (1) /* previous block is allocated */
#define P_FLAG_MASK (0x00000002)
#define BLOCK_SIZE_MULTIPLIER (3)
#define BLOCK_SIZE_MASK (0xfffffff4)
#define REMAINDER_SIZE_MULTIPLIER BLOCK_SIZE_MULTIPLIER
#define REMAINDER_SIZE_MASK ((0xffffffff << 32) & BLOCK_SIZE_MASK)

/* need to update when *_SIZE_MULTIPLIER changes. */
#define ALIGN_MEM_SIZE(size) (((size + 0x7) >> 3) << 3)
#define ALIGN_MEM_SIZE_TRUNC(size) ((size >> 3) << 3)

typedef void *mem_t;
typedef uint64_t mem_size_t;
typedef uint32_t block_head_t;
typedef uint32_t block_size_t;

struct mem_pool
{
  uint64_t free_memory;
  union
  {
    uint64_t _padding;
    struct sorted_block *addr;
  } sorted_block;
  union
  {
    uint64_t _padding;
    struct sorted_block *addr;
  } remainder_block;
  union
  {
    uint64_t _padding;
    struct sorted_block *addr;
  } remainder_block_end; /* should not be dereferenced */
  union
  {
    uint64_t _padding;
    struct fast_block *addr;
  } fast_bins[FAST_BIN_LENGTH];
};

struct fast_block
{
  block_head_t head;
  union
  {
    uint32_t _padding; /* TODO! update for 64 bits system */
    struct fast_block *next;
    void *payload;
  };
};

struct sorted_block
{
  block_head_t head;
  union
  {
    struct
    {
      uint32_t pred_offset;
      uint32_t succ_offset;
      // padding
      // uint32_t footer;
    };
    void *payload;
  };
};

inline bool
block_is_allocated (block_head_t const *head)
{
  return (*head) & A_FLAG_MASK;
}

inline void
block_set_A_flag (block_head_t *head, bool allocated)
{
  *head = allocated ? (*head | A_FLAG_MASK) : (*head & (~A_FLAG_MASK));
}

inline bool
prev_block_is_allocated (block_head_t const *head)
{
  return (*head) & P_FLAG_MASK;
}

inline void
block_set_P_flag (block_head_t *head, bool allocated)
{
  *head = allocated ? (*head | P_FLAG_MASK) : (*head & (~P_FLAG_MASK));
}

inline block_size_t
block_get_size (block_head_t const *head)
{
  return (*head) & BLOCK_SIZE_MASK;
}

/**
 * since the block is 8-bytes aligned, the smallest 8's multiple greater than
 * size is used instead.
 **/
inline void
block_set_size (block_head_t *head, block_size_t size)
{
  *head = (*head & (~BLOCK_SIZE_MASK)) /* preserve flags */
          | ALIGN_MEM_SIZE (size);     /* ensure rounds up */
}

inline mem_size_t
get_remainder_size (struct mem_pool const *pool)
{
  return pool->remainder_block_end.addr - pool->remainder_block.addr;
}

bool deep_mem_init (void *mem, uint32_t size);

void deep_mem_destroy (void);

void *deep_malloc (uint32_t size);

void *deep_realloc (void *ptr, uint32_t size);

void deep_free (void *ptr);

bool deep_mem_migrate (void *new_mem, uint32_t size);

#endif /* _DEEP_MEM_ALLOC_H */
