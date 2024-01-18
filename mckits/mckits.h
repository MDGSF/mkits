#ifndef MKITS_MCKITS_MCKITS_H_
#define MKITS_MCKITS_MCKITS_H_

#ifdef __cplusplus
extern "C" {
#endif

// mstl
#include "mckits_adt_hashmap.h"
#include "mckits_adt_heap.h"
#include "mckits_adt_list.h"
#include "mckits_adt_nlist.h"
#include "mckits_adt_rbtree.h"
#include "mckits_adt_ring.h"
#include "mckits_adt_skiplist.h"
#include "mckits_array.h"
#include "mckits_config.h"
#include "mckits_malloc.h"
#include "mckits_mstl_utils.h"
#include "mckits_string.h"
#include "mckits_vector.h"

// platform
#include "mckits_mfile.h"
#include "mckits_mos.h"
#include "mckits_msock.h"
#include "mckits_rawpipe.h"
#include "mckits_thread.h"

// core
// core/encoding
#include "mckits_encoding_base32.h"
#include "mckits_encoding_base64.h"
#include "mckits_encoding_binary.h"
#include "mckits_encoding_hex.h"
#include "mckits_encoding_iniparser.h"
#include "mckits_encoding_json.h"
#include "mckits_encoding_toml.h"
#include "mckits_endian.h"

// core/hash
#include "mckits_crc.h"
#include "mckits_hash_fnv.h"
#include "mckits_hash_murmur.h"

// core/queue
#include "mckits_adt_flowqueue.h"
#include "mckits_adt_mpmcqueue.h"

// core/thread
#include "mckits_atomic.h"
#include "mckits_rwlock.h"
#include "mckits_rwlockp.h"
#include "mckits_spinlock.h"

// core/others
#include "mckits_core_utils.h"
#include "mckits_mlog.h"
#include "mckits_mrandom.h"
#include "mckits_mtime.h"
#include "mckits_strconv.h"

#ifdef __cplusplus
}
#endif

#endif
