#include "mckits/core/mckits_socket_poller.h"

#include "mckits/mlibc/mckits_config.h"

#ifdef MCKITS_OS_LINUX
#include "src/mckits/core/mckits_socket_poller_epoll.c"
#endif

#ifdef MCKITS_OS_BSD
#include "src/mckits/core/mckits_socket_poller_kqueue.c"
#endif
