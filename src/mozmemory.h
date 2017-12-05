/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozmemory_h
#define mozmemory_h

/*
 * This header is meant to be used when the following functions are
 * necessary:
 *   - malloc_good_size (used to be called je_malloc_usable_in_advance)
 *   - jemalloc_stats
 *   - jemalloc_purge_freed_pages
 *   - jemalloc_free_dirty_pages
 *   - jemalloc_thread_local_arena
 *   - jemalloc_ptr_info
 */

#ifndef MOZ_MEMORY
#  error Should not include mozmemory.h when MOZ_MEMORY is not set
#endif

#include "mozmemory_wrap.h"
#include "mozilla/Attributes.h"
#include "mozilla/Types.h"
#include "mozjemalloc_types.h"

/*
 * On OSX, malloc/malloc.h contains the declaration for malloc_good_size,
 * which will call back in jemalloc, through the zone allocator so just use it.
 */
#ifdef XP_DARWIN
#  include <malloc/malloc.h>
#else
MOZ_MEMORY_API size_t malloc_good_size_impl(size_t size);

/* Note: the MOZ_GLUE_IN_PROGRAM ifdef below is there to avoid -Werror turning
 * the protective if into errors. MOZ_GLUE_IN_PROGRAM is what triggers MFBT_API
 * to use weak imports. */

static inline size_t _malloc_good_size(size_t size) {
#  if defined(MOZ_GLUE_IN_PROGRAM) && !defined(IMPL_MFBT)
  if (!malloc_good_size)
    return size;
#  endif
  return malloc_good_size_impl(size);
}

#  define malloc_good_size _malloc_good_size
#endif

#define MALLOC_DECL(name, return_type, ...) \
  MOZ_JEMALLOC_API return_type name(__VA_ARGS__);
#define MALLOC_FUNCS MALLOC_FUNCS_JEMALLOC
#include "malloc_decls.h"

#endif /* mozmemory_h */