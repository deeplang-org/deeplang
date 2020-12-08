#include "deep_mem_alloc.h"
#include "random/random.h"
#include "string.h"

struct mem_pool *pool;

static void *deep_malloc_fast_bins (uint32_t size);
static void *deep_malloc_sorted_bins (uint32_t size);
static void deep_free_fast_bins (void *ptr);
static void deep_free_sorted_bins (void *ptr);

/* helper functions for maintining the sorted_block skiplist */
static void _split_into_two_sorted_blocks (struct sorted_block *block,
                                           uint32_t aligned_size);
static void _merge_into_single_block (struct sorted_block *curr,
                                      struct sorted_block *next);

static struct sorted_block *
_allocate_block_from_skiplist (uint32_t aligned_size);

static inline bool _sorted_block_is_in_skiplist (struct sorted_block *block);
static struct sorted_block *
_find_sorted_block_by_size_on_index (struct sorted_block *node, uint32_t size,
                                     uint32_t index_level);
static struct sorted_block *
_find_sorted_block_by_size (struct sorted_block *node, uint32_t size);
static void _insert_sorted_block_to_skiplist (struct sorted_block *block);
static void _remove_sorted_block_from_skiplist (struct sorted_block *block);

bool
deep_mem_init (void *mem, uint32_t size)
{
  assert (mem != NULL);

  if (size < sizeof (struct mem_pool))
    {
      return false; /* given buffer is too small */
    }

  memset (mem, 0, size);
  mem_size_t aligned_size = ALIGN_MEM_SIZE_TRUNC (size);

  pool = (struct mem_pool *)mem;
  pool->free_memory = aligned_size - sizeof (struct mem_pool)
                      - sizeof (struct sorted_block) - sizeof (block_head_t);
  /* the first node in the list, to simplify implementation */
  pool->sorted_block.addr
      = (struct sorted_block *)(get_pointer_by_offset_in_bytes (
          mem, sizeof (struct mem_pool)));
  /* all other fields are set as 0 */
  pool->sorted_block.addr->level_of_indices = SORTED_BLOCK_INDICES_LEVEL;

  pool->remainder_block.addr
      = (struct sorted_block *)(get_pointer_by_offset_in_bytes (
          mem, sizeof (struct mem_pool) + sizeof (struct sorted_block)));
  pool->remainder_block_end.addr
      = (struct sorted_block *)(get_pointer_by_offset_in_bytes (
          mem, aligned_size - 8)); // -8 for safety
  for (int i = 0; i < FAST_BIN_LENGTH; ++i)
    {
      pool->fast_bins[i].addr = NULL;
    }
  // initialise remainder block's head
  block_set_A_flag (&pool->remainder_block.addr->head, false);
  block_set_P_flag (&pool->remainder_block.addr->head, true);

  return true;
}

void
deep_mem_destroy (void)
{
  pool = NULL;
}

void *
deep_malloc (uint32_t size)
{
  assert (pool != NULL);

  if (pool->free_memory < size)
    {
      return NULL;
    }
  if (size <= FAST_BIN_MAX_SIZE)
    {
      return deep_malloc_fast_bins (size);
    }
  return deep_malloc_sorted_bins (size);
}

static void *
deep_malloc_fast_bins (uint32_t size)
{
  block_size_t aligned_size = ALIGN_MEM_SIZE (size + sizeof (block_head_t));
  uint32_t offset = (aligned_size >> 3) - 1;
  bool P_flag = false;
  struct fast_block *ret = NULL;
  block_size_t payload_size;

  if (pool->fast_bins[offset].addr != NULL)
    {
      ret = pool->fast_bins[offset].addr;
      pool->fast_bins[offset].addr = ret->next;
      P_flag = prev_block_is_allocated (&ret->head);
      payload_size = block_get_size (&ret->head) - sizeof (block_head_t);
    }
  else if (aligned_size <= get_remainder_size (pool))
    {
      ret = (struct fast_block *)(get_pointer_by_offset_in_bytes (
          pool->remainder_block_end.addr,
          -(int64_t)aligned_size - sizeof (block_head_t)));
      pool->remainder_block_end.addr = (struct sorted_block *)ret;

      payload_size = aligned_size - sizeof (block_head_t);
      block_set_size (&ret->head, aligned_size);
      pool->free_memory -= sizeof (block_head_t);
    }
  else
    {
      return NULL;
    }

  memset (&ret->payload, 0, payload_size);
  block_set_A_flag (&ret->head, true);
  block_set_P_flag (&ret->head, P_flag);
  pool->free_memory -= payload_size;

  return &ret->payload;
}

static void *
deep_malloc_sorted_bins (uint32_t size)
{
  block_size_t aligned_size = ALIGN_MEM_SIZE (size + sizeof (block_head_t));
  struct sorted_block *ret = NULL;
  block_size_t payload_size;

  if ((pool->sorted_block.addr != NULL)
      && ((ret = _allocate_block_from_skiplist (aligned_size)) != NULL))
    {
      /* pass */
    }
  else if (aligned_size <= get_remainder_size (pool))
    {
      /* no suitable sorted_block */
      ret = (struct sorted_block *)pool->remainder_block.addr;
      block_set_size (&ret->head, get_remainder_size (pool));
      _split_into_two_sorted_blocks (ret, aligned_size);
    }
  else
    {
      return NULL;
    }

  payload_size = aligned_size - sizeof (block_head_t);
  memset (&ret->payload, 0, payload_size);
  block_set_A_flag (&ret->head, true);
  block_set_P_flag (&get_block_by_offset (ret, aligned_size)->head, true);
  pool->free_memory -= payload_size;

  return &ret->payload;
}

void *
deep_realloc (void *ptr, uint32_t size)
{
  return NULL;
}

void
deep_free (void *ptr)
{
  assert (pool != NULL);

  void *head
      = get_pointer_by_offset_in_bytes (ptr, -(int64_t)sizeof (block_head_t));

  if (ptr == NULL || !block_is_allocated ((block_head_t *)head))
    {
      return;
    }
  block_size_t size = block_get_size ((block_head_t *)head);

  if (size <= FAST_BIN_MAX_SIZE)
    {
      deep_free_fast_bins (head);
    }
  else
    {
      deep_free_sorted_bins (head);
    }
}

static void
deep_free_fast_bins (void *ptr)
{
  struct fast_block *block = ptr;
  block_size_t payload_size
      = block_get_size (&block->head) - sizeof (block_head_t);
  uint32_t offset = ((payload_size + sizeof (block_head_t)) >> 3) - 1;

  memset (block->payload, 0, payload_size);

  block_set_A_flag (&block->head, false);
  block->next = pool->fast_bins[offset].addr;
  pool->fast_bins[offset].addr = block;

  pool->free_memory += payload_size;
}

static void
deep_free_sorted_bins (void *ptr)
{
  struct sorted_block *block = ptr;
  struct sorted_block *the_other = NULL;
  block_size_t payload_size
      = block_get_size (&block->head) - sizeof (block_head_t);

  memset (block->payload, 0, payload_size);

  block_set_A_flag (&block->head, false);

  /* try to merge */
  if (!prev_block_is_allocated (&block->head))
    {
      block_size_t prev_size
          = block_get_size ((block_head_t *)(block - sizeof (block_head_t)));
      the_other = get_block_by_offset (block, -((int32_t)prev_size));
      _merge_into_single_block (the_other, block);

      block = the_other;
    }

  the_other = get_block_by_offset (block, block_get_size (&block->head));
  if (!block_is_allocated (&the_other->head))
    {
      _merge_into_single_block (block, the_other);
    }

  if (!_sorted_block_is_in_skiplist (block))
    {
      _insert_sorted_block_to_skiplist (block);
    }

  pool->free_memory += payload_size;
}

bool
deep_mem_migrate (void *new_mem, uint32_t size)
{
  return false;
}

/* helper functions for maintining the sorted_block skiplist */
static void
_split_into_two_sorted_blocks (struct sorted_block *block,
                               uint32_t aligned_size)
{
  struct sorted_block *new_block = get_block_by_offset (block, aligned_size);
  block_size_t new_block_size = block_get_size (&block->head) - aligned_size;

  memset (new_block, 0, new_block_size);
  block_set_size (&new_block->head, new_block_size);
  block_set_A_flag (&new_block->head, false);
  block_set_P_flag (&new_block->head, false); /* by default */
  _insert_sorted_block_to_skiplist (new_block);

  block_set_size (&block->head, aligned_size);
  pool->free_memory -= sizeof (block_head_t);
}

/**
 * Assuming `curr` and `next` are contiguous in memory address,
 * where curr < next
 * Attempt to remove both nodes from list, merge them, and insert the merged.
 * NOTE:
 *   - will update `free_memory` of releasing `sizeof (block_head_t)` to pool
 **/
static void
_merge_into_single_block (struct sorted_block *curr, struct sorted_block *next)
{
  _remove_sorted_block_from_skiplist (curr);
  _remove_sorted_block_from_skiplist (next);

  block_size_t new_size
      = block_get_size (&curr->head) + block_get_size (&next->head);

  block_set_size (&curr->head, new_size);
  memset (&curr->payload, 0, new_size - sizeof (curr->head));
  // copy over new head info to footer
  *(block_head_t *)get_pointer_by_offset_in_bytes (
      &curr->head, new_size - sizeof (block_head_t))
      = curr->head;

  _insert_sorted_block_to_skiplist (curr);

  pool->free_memory += sizeof (block_head_t);
}

/** Obtain a most apporiate block from sorted_list if possible.
 *
 * - Obtain one with exact same size.
 * - Obtain one with bigger size, but split into two sorted blocks
 *   - returns the part with exactly same size
 *   - insert the rest into sorted_block skiplist
 *   - NOTE: this requires the block found be at least
 *           (`aligned_size + SORTED_BIN_MIN_SIZE`) big
 * - NULL
 *
 * NOTE: The obtained block will be **removed** from the skiplist.
 **/
static struct sorted_block *
_allocate_block_from_skiplist (uint32_t aligned_size)
{
  struct sorted_block *ret = NULL;

  if ((pool->sorted_block.addr == NULL)
      || ((ret = _find_sorted_block_by_size (pool->sorted_block.addr,
                                             aligned_size))
          == NULL))
    {
      return NULL;
    }
  if (block_get_size (&ret->head) != aligned_size)
    {
      if ((block_get_size (&ret->head) < aligned_size + SORTED_BIN_MIN_SIZE)
          && (ret = _find_sorted_block_by_size (
                  ret, aligned_size + SORTED_BIN_MIN_SIZE))
                 == NULL)
        {
          return NULL;
        }
      _split_into_two_sorted_blocks (ret, aligned_size);
    }
  _remove_sorted_block_from_skiplist (ret);

  return ret;
}

static inline bool
_sorted_block_is_in_skiplist (struct sorted_block *block)
{
  assert (block != NULL);
  return (block->pred_offset != 0 || block->level_of_indices != 0);
}

/**
 *  returns a block with desired size on the list of given index level;
 * if not possible, the greatest one that is smaller than desired.
 *
 * NOTE:
 *   - there will always be an infimum due to the existence of head
 *   - this function will not check nodes on other index level
 *   - this function will not check if there are any predecessor in the chain
 *     with same key. It assumes the `node` given has embedded all indices.
 **/
static struct sorted_block *
_find_sorted_block_by_size_on_index (struct sorted_block *node, uint32_t size,
                                     uint32_t index_level)
{
  assert (node != NULL);

  struct sorted_block *curr = node;
  struct sorted_block *prev = curr;

  while (block_get_size (&curr->head) < size)
    {
      prev = curr; /* curr is the candidate of infimum. */
      /* reached the end of the skiplist or the biggest smaller sorted block */
      if (index_level >= SORTED_BLOCK_INDICES_LEVEL
          || curr->offsets[index_level] == 0)
        {
          break;
        }
      curr = get_block_by_offset (curr, curr->offsets[index_level]);
    }

  /* return a node with no indices to avoid copying indices. */
  if (block_get_size (&curr->head) == size && curr->succ_offset != 0)
    {
      return get_block_by_offset (curr, curr->succ_offset);
    }

  return prev;
}

/**
 *  returns a block with desired size; if not possible, the least greater one
 *
 * NOTE:
 *   - returns NULL when supremum is not in the list
 **/
static struct sorted_block *
_find_sorted_block_by_size (struct sorted_block *node, uint32_t size)
{
  assert (node != NULL);

  struct sorted_block *curr = node;

  /* indices should only exists on first node in each sub-list. */
  while (curr->pred_offset != 0)
    {
      curr = get_block_by_offset (curr, curr->pred_offset);
    }

  while (block_get_size (&curr->head) < size)
    {
      uint32_t index_level
          = SORTED_BLOCK_INDICES_LEVEL - curr->level_of_indices;

      /* skip non-existing indices, to node with size <= than desired */
      while (index_level < SORTED_BLOCK_INDICES_LEVEL
             || curr->offsets[index_level] == 0
             || (block_get_size (
                     &get_block_by_offset (curr, curr->offsets[index_level])
                          ->head)
                 > size))
        {
          index_level++;
        }

      /* reached the end of the skiplist or the biggest smaller sorted block */
      if (index_level >= SORTED_BLOCK_INDICES_LEVEL
          || curr->offsets[index_level] == 0)
        {
          break;
        }

      /* will not be NULL as curr's size is smaller than size */
      curr = _find_sorted_block_by_size_on_index (curr, size, index_level);
    }

  /* all nodes are smaller than required. */
  if (block_get_size (&curr->head) < size)
    {
      return NULL;
    }

  /* return a node with no indices to avoid copying indices. */
  if (curr->succ_offset != 0)
    {
      curr = get_block_by_offset (curr, curr->succ_offset);
    }

  return curr;
}

static void
_insert_sorted_block_to_skiplist (struct sorted_block *block)
{
  assert (block != NULL);
  assert (pool->sorted_block.addr != NULL);

  block_size_t size = block_get_size (&block->head);
  struct sorted_block *pos
      = _find_sorted_block_by_size (pool->sorted_block.addr, size);

  /* insert into the chain with same size. */
  if (pos != NULL && block_get_size (&pos->head) == size)
    {
      block->pred_offset = get_offset_between_blocks (block, pos);
      if (pos->succ_offset != 0)
        {
          block->succ_offset
              = pos->succ_offset - get_offset_between_blocks (pos, block);
        }
      else
        {
          block->succ_offset = 0; /* end of chain */
        }
      pos->succ_offset = get_offset_between_blocks (pos, block);

      return;
    }

  block->level_of_indices
      = ((uint32_t) (next () >> 32)) % SORTED_BLOCK_INDICES_LEVEL + 1;

  for (uint32_t index_level
       = SORTED_BLOCK_INDICES_LEVEL - block->level_of_indices;
       index_level < SORTED_BLOCK_INDICES_LEVEL; ++index_level)
    {
      pos = _find_sorted_block_by_size_on_index (pool->sorted_block.addr, size,
                                                 index_level);
      if (pos->offsets[index_level] != 0)
        {
          block->offsets[index_level]
              = pos->offsets[index_level]
                - get_offset_between_blocks (pos, block);
        }
      else
        {
          block->offsets[index_level] = 0;
        }
      pos->offsets[index_level] = get_offset_between_blocks (pos, block);
    }
}

/**
 * Remove the node and update all indices / offsets.
 * May traverse the list multiple times
 *
 * NOTE: never removes a node with offsets when it has children in the chain
 **/
static void
_remove_sorted_block_from_skiplist (struct sorted_block *block)
{
  assert (block != NULL);
  /* considering a node which is not in the skiplist */
  /* assert (block->level_of_indices != 0 || block->pred_offset != 0); */

  struct sorted_block *prev = NULL;
  block_size_t size = block_get_size (&block->head);

  for (uint32_t index_level
       = SORTED_BLOCK_INDICES_LEVEL - block->level_of_indices;
       index_level < SORTED_BLOCK_INDICES_LEVEL; ++index_level)
    {
      /* -1 to find the strictly smaller node. */
      prev = _find_sorted_block_by_size_on_index (pool->sorted_block.addr,
                                                  size - 1, index_level);
      if (block->offsets[index_level] != 0)
        {
          prev->offsets[index_level] += block->offsets[index_level];
        }
      else
        {
          prev->offsets[index_level] = 0;
        }
    }

  if (block->pred_offset != 0)
    {
      if (block->succ_offset != 0)
        {
          get_block_by_offset (block, block->pred_offset)->succ_offset
              += block->succ_offset;
          get_block_by_offset (block, block->succ_offset)->pred_offset
              += block->pred_offset;
        }
      else
        {
          get_block_by_offset (block, block->pred_offset)->succ_offset = 0;
        }
    }
  /* no other cases, as if it is the first node, it should be the only node. */
}
