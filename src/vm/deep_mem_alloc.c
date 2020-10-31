#include "deep_mem_alloc.h"
#include "string.h"

struct mem_pool *pool;

static void *deep_malloc_fast_bins (uint32_t size);
static void *deep_malloc_sorted_bins (uint32_t size);
static void deep_free_fast_bins (void *ptr);
static void deep_free_sorted_bins (void *ptr);

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
  pool->free_memory = aligned_size - sizeof (struct mem_pool);
  pool->sorted_block.addr = (struct sorted_block *)&(pool->sorted_block.addr);
  pool->remainder_block.addr
      = (struct sorted_block *)(mem + sizeof (struct mem_pool));
  pool->remainder_block_end.addr = (struct sorted_block *)(mem + aligned_size);
  for (int i = 0; i < FAST_BIN_LENGTH; ++i)
    {
      pool->fast_bins[i].addr
          = (struct fast_block *)&(pool->fast_bins[i].addr);
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

  if (pool->fast_bins[offset].addr
      != (struct fast_block *)(&pool->fast_bins[offset].addr))
    {
      ret = pool->fast_bins[offset].addr;
      pool->fast_bins[offset].addr = ret->next;
      P_flag = prev_block_is_allocated (&ret->head);
      payload_size = block_get_size (&ret->head);
    }
  else if (aligned_size <= get_remainder_size (pool))
    {
      ret = (struct fast_block *)(((uint8_t *)pool->remainder_block_end.addr)
                                  - aligned_size);
      payload_size = aligned_size - sizeof (block_head_t);
      block_set_size (&ret->head, payload_size);
      pool->free_memory -= sizeof (block_head_t);
    }

  memset (ret->payload, 0, payload_size);
  block_set_A_flag (&ret->head, true);
  block_set_P_flag (&ret->head, P_flag);
  pool->free_memory -= payload_size;

  return ret->payload;
}

static void *
deep_malloc_sorted_bins (uint32_t size)
{
  return NULL;
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
  if (ptr == NULL)
    {
      return;
    }
  void *head = (uint8_t *)ptr - sizeof (block_head_t);
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
  block_size_t payload_size = block_get_size (&block->head);
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
  return;
}

bool
deep_mem_migrate (void *new_mem, uint32_t size)
{
  return false;
}
