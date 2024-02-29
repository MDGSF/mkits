#ifndef MKITS_INCLUDE_MCKITS_MCKITS_H_
#define MKITS_INCLUDE_MCKITS_MCKITS_H_

#ifdef __cplusplus
extern "C" {
#endif

// mlibc
#include "mckits/mlibc/mckits_config.h"
#include "mckits/mlibc/mckits_cwrap.h"
#include "mckits/mlibc/mckits_malloc.h"
#include "mckits/mlibc/mckits_mlibc_utils.h"

// mstl
#include "mckits/mstl/mckits_array.h"
#include "mckits/mstl/mckits_hashmap.h"
#include "mckits/mstl/mckits_hashset.h"
#include "mckits/mstl/mckits_heap.h"
#include "mckits/mstl/mckits_list.h"
#include "mckits/mstl/mckits_nlist.h"
#include "mckits/mstl/mckits_rbtree.h"
#include "mckits/mstl/mckits_ring.h"
#include "mckits/mstl/mckits_skiplist.h"
#include "mckits/mstl/mckits_strconv.h"
#include "mckits/mstl/mckits_string.h"
#include "mckits/mstl/mckits_vecdeque.h"
#include "mckits/mstl/mckits_vector.h"

// mstl/encoding
#include "mckits/mstl/encoding/mckits_encoding_base32.h"
#include "mckits/mstl/encoding/mckits_encoding_base64.h"
#include "mckits/mstl/encoding/mckits_encoding_binary.h"
#include "mckits/mstl/encoding/mckits_encoding_hex.h"

// mstl/hash
#include "mckits/mstl/hash/mckits_crc.h"
#include "mckits/mstl/hash/mckits_hash_fnv.h"
#include "mckits/mstl/hash/mckits_hash_murmur.h"
#include "mckits/mstl/hash/mckits_hash_sip.h"
#include "mckits/mstl/hash/mckits_hash_xxhash.h"

// core
// core/encoding
#include "mckits/core/encoding/mckits_encoding_iniparser.h"
#include "mckits/core/encoding/mckits_encoding_json.h"
#include "mckits/core/encoding/mckits_encoding_toml.h"
#include "mckits/core/encoding/mckits_endian.h"

// core/queue
#include "mckits/core/queue/mckits_flowqueue.h"
#include "mckits/core/queue/mckits_mpmcqueue.h"

// core/thread
#include "mckits/core/thread/mckits_atomic.h"
#include "mckits/core/thread/mckits_rwlock.h"
#include "mckits/core/thread/mckits_rwlockp.h"
#include "mckits/core/thread/mckits_spinlock.h"

// core/others
#include "mckits/core/mckits_core_utils.h"
#include "mckits/core/mckits_daemon.h"
#include "mckits/core/mckits_mfile.h"
#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_mos.h"
#include "mckits/core/mckits_mrandom.h"
#include "mckits/core/mckits_msock.h"
#include "mckits/core/mckits_mtime.h"
#include "mckits/core/mckits_rawpipe.h"
#include "mckits/core/mckits_socket_poller.h"
#include "mckits/core/mckits_thread.h"

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_MCKITS_H_
