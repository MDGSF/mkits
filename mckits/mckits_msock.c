#include "mckits_msock.h"

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "mckits_mlog.h"

int mckits_set_reuse_addr(int fd, int on) {
  int opt = on ? 1 : 0;
  int ret =
      setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, (socklen_t)(sizeof(opt)));
  if (ret == -1) {
    verbolog("setsockopt SO_REUSEADDR failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_set_reuse_port(int fd, int on) {
  int opt = on ? 1 : 0;
  int ret =
      setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, (socklen_t)(sizeof(opt)));
  if (ret == -1) {
    verbolog("setsockopt SO_REUSEPORT failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_set_non_blocking(int fd, int on) {
  // Set socket nonblocking.
  // Note that fcntl(2) and F_GETFL and F_SETFL can't be
  // interrupted by a signal.
  int flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    verbolog("fcntl F_GETFL failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }

  if (on) {
    flags |= O_NONBLOCK;
  } else {
    int nonblock = O_NONBLOCK;
    flags &= ~nonblock;
  }

  if (fcntl(fd, F_SETFL, flags) == -1) {
    verbolog("fcntl F_SETFL failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }
  return 0;
}

int mckits_set_tcp_nodelay(int fd, int on) {
  int opt = on ? 1 : 0;
  int ret =
      setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &opt, (socklen_t)(sizeof(opt)));
  if (ret == -1) {
    verbolog("setsockopt TCP_NODELAY failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_enable_tcp_nodelay(int fd) { return mckits_set_tcp_nodelay(fd, 1); }

int mckits_disable_tcp_nodelay(int fd) { return mckits_set_tcp_nodelay(fd, 0); }

int mckits_set_close_wait(int fd, int second) {
  struct linger slinger;
  slinger.l_onoff = (second > 0) ? 1 : 0;  // Nonzero to linger on close.
  slinger.l_linger = second;               // Time to linger
  int ret =
      setsockopt(fd, SOL_SOCKET, SO_LINGER, &slinger, sizeof(struct linger));
  if (ret == -1) {
    verbolog("setsockopt SO_LINGER failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_set_nosigpipe(int fd) {
#if defined(SO_NOSIGPIPE)
  int opt = 1;
  int ret = setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof(opt));
  if (ret == -1) {
    verbolog("setsockopt SO_NOSIGPIPE failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
#elif defined(MSG_NOSIGNAL)
  int opt = 1;
  int ret = setsockopt(fd, SOL_SOCKET, MSG_NOSIGNAL, &opt, sizeof(opt));
  if (ret == -1) {
    verbolog("setsockopt MSG_NOSIGNAL failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
#else
  return -1;
#endif
}

int mckits_set_recvbuf(int fd, int size) {
  int ret = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
  if (ret == -1) {
    verbolog("setsockopt SO_RCVBUF failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_set_sendbuf(int fd, int size) {
  int ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));
  if (ret == -1) {
    verbolog("setsockopt SO_SNDBUF failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_set_keeyalive(int fd, int on, int interval, int idle, int times) {
  int opt = on ? 1 : 0;
  int ret =
      setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &opt, (socklen_t)(sizeof(opt)));
  if (ret == -1) {
    verbolog("setsockopt SO_KEEPALIVE failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }

  if (!on) {
    return 0;
  }

  ret = setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &idle, (socklen_t)(sizeof(idle)));
  if (ret == -1) {
    verbolog("setsockopt TCP_KEEPIDLE failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }

  ret = setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &interval,
                   (socklen_t)(sizeof(interval)));
  if (ret == -1) {
    verbolog("setsockopt TCP_KEEPINTVL failed, fd: %d: %s", fd,
             strerror(errno));
    return -1;
  }

  ret =
      setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &times, (socklen_t)(sizeof(times)));
  if (ret == -1) {
    verbolog("setsockopt TCP_KEEPCNT failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }

  return 0;
}

int mckits_set_broadcast(int fd, int on) {
  int opt = on ? 1 : 0;
  int ret =
      setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &opt, (socklen_t)(sizeof(opt)));
  if (ret == -1) {
    verbolog("setsockopt SO_BROADCAST failed, fd: %d: %s", fd, strerror(errno));
  }
  return ret;
}

int mckits_set_close_exec(int fd, int on) {
  int flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    verbolog("fcntl F_GETFL failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }
  if (on) {
    flags |= FD_CLOEXEC;
  } else {
    int cloexec = FD_CLOEXEC;
    flags &= ~cloexec;
  }
  if (fcntl(fd, F_SETFL, flags) == -1) {
    verbolog("fcntl F_SETFL failed, fd: %d: %s", fd, strerror(errno));
    return -1;
  }
  return 0;
}

/*
@brief: Convert IPv4 and IPv6 addresses from binary to text form.
@param af[in]: AF_INET, AF_INET6
@param src[in]:
  if af == AF_INET then
    - src points to a struct in_addr
    - return "ddd.ddd.ddd.ddd"
  if af == AF_INET6 then
    - src points to a struct in6_addr
    - return IPv6 text form
@return
  On success, returns a non-null pointer to dst.
  On error, NULL is returned.
*/
static const char* my_inet_ntop(int af, const void* src, char* dst,
                                size_t size) {
  return inet_ntop(af, src, dst, size);
}

const char* mckits_inet_ntoa4(const struct in_addr* addr, char* dst,
                              size_t size) {
  return my_inet_ntop(AF_INET, addr, dst, size);
}

const char* mckits_inet_ntoa6(const struct in6_addr* addr, char* dst,
                              size_t size) {
  return my_inet_ntop(AF_INET6, addr, dst, size);
}

const char* mckits_inet_ntoas(const struct sockaddr* addr, char* dst,
                              size_t size) {
  switch (addr->sa_family) {
    case AF_INET:
      return mckits_inet_ntoa4(&(((struct sockaddr_in*)addr)->sin_addr), dst,
                               size);
    case AF_INET6:
      return mckits_inet_ntoa6(&(((struct sockaddr_in6*)addr)->sin6_addr), dst,
                               size);
    default:
      return NULL;
  }
}

uint16_t mckits_inet_port(const struct sockaddr* addr) {
  switch (addr->sa_family) {
    case AF_INET:
      return ntohs(((struct sockaddr_in*)addr)->sin_port);
    case AF_INET6:
      return ntohs(((struct sockaddr_in6*)addr)->sin6_port);
    default:
      return 0;
  }
}
