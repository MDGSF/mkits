#ifndef MKITS_MCKITS_MCKITS_MSOCK_H_
#define MKITS_MCKITS_MCKITS_MSOCK_H_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>

#define SOCKET_DEFAULT_BUF_SIZE (256 * 1024)
#define TCP_KEEPALIVE_INTERVAL 30
#define TCP_KEEPALIVE_PROBE_TIMES 9
#define TCP_KEEPALIVE_TIME 30

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Set socket SO_REUSEADDR.
@param fd[in]: Socket fd.
@param on[in]: 1 means enable, 0 means disable.
@return: 0 means success, else failed
*/
int mckits_set_reuse_addr(int fd, int on);

/*
@brief: Set socket SO_REUSEPORT.
@param fd[in]: Socket fd.
@param on[in]: 1 means enable, 0 means disable.
@return: 0 means success, else failed
*/
int mckits_set_reuse_port(int fd, int on);

/*
@brief: Set socket non-blocking.
@param on[in]: 1 means non-blocking, 0 means blocking.
@return: 0 mean success, else failed
*/
int mckits_set_non_blocking(int fd, int on);

/*
@brief: Enable or disable TCP_NODELAY
@param fd[in]: Socket fd.
@param on[in]: 1 means enable, 0 means disable.
@return: 0 means success, else failed
*/
int mckits_set_tcp_nodelay(int fd, int on);

/*
@brief: Enable TCP_NODELAY. The same as set_tcp_nodelay(int fd, 1).
@param fd[in]: Socket fd.
@return: 0 mean success, else failed
*/
int mckits_enable_tcp_nodelay(int fd);

/*
@brief: Disable TCP_NODELAY. The same as set_tcp_nodelay(int fd, 0)
@param fd[in]: Socket fd.
@return: 0 mean success, else failed
*/
int mckits_disable_tcp_nodelay(int fd);

/*
@brief: Enable SO_LINGER feature.
@param fd[in]: Socket fd.
@param second[in]:
  if second > 0, enable SO_LINGER, and linger time is second.
  if second <= 0, disable SO_LINGER.
@return: 0 mean success, else failed
*/
int mckits_set_close_wait(int fd, int second);

/*
@brief: Let socket ignore SIGPIPE.
  You can use signal(SIGPIPE, SIG_IGN) to make whole program ignore SIGPIPE.
@return: 0 mean success, else failed
*/
int mckits_set_nosigpipe(int fd);

/*
@brief: Set socket receive buffer size.
@param fd[in]: Socket fd.
@param size[in]: Receive buffer size. (SOCKET_DEFAULT_BUF_SIZE)
@return: 0 mean success, else failed
*/
int mckits_set_recvbuf(int fd, int size);

/*
@brief: Set socket send buffer size.
@param fd[in]: Socket fd.
@param size[in]: Send buffer size. (SOCKET_DEFAULT_BUF_SIZE)
@return: 0 mean success, else failed
*/
int mckits_set_sendbuf(int fd, int size);

/*
@brief: Enable or disable TCP KeepAlive feature.
@param fd[in]: Socket fd.
@param on[in]: 1 means enable, 0 means disable.
@param interval[in]: interval time between two prob (second)
  (TCP_KEEPALIVE_INTERVAL)
@param idle[in]: keepalive idle time (second) (TCP_KEEPALIVE_TIME)
@param times[in]: probe times. (TCP_KEEPALIVE_PROBE_TIMES)
@return: 0 means success, else failed
*/
int mckits_set_keeyalive(int fd, int on, int interval, int idle, int times);

/*
@brief: Set socket can send and recv broadcast message.
@param fd[in]: Socket fd.
@param on[in]: 1 means enable, 0 means disable.
@return: 0 means success, else failed
*/
int mckits_set_broadcast(int fd, int on);

/*
@brief: Enable or disable FD_CLOEXEC feature.
@param fd[in]: Socket or file fd.
@param on[in]: 1 means enable, 0 means disable.
@return: 0 means success, else failed
*/
int mckits_set_close_exec(int fd, int on);

/*
@brief: Get ip address text form from in_addr/in6_addr/sockaddr。
@param addr[in]: address struct.
@param dst[out]: memory buffer used to store output string.
@param size[in]: dst memory bufffer size.
@return:
  On success, returns a non-null pointer to dst. "ddd.ddd.ddd.ddd" if ipv4.
  On error, NULL is returned.
*/
const char* mckits_inet_ntoa4(const struct in_addr* addr, char* dst,
                              size_t size);
const char* mckits_inet_ntoa6(const struct in6_addr* addr, char* dst,
                              size_t size);
const char* mckits_inet_ntoas(const struct sockaddr* addr, char* dst,
                              size_t size);

/*
@brief: Get port number from sock_addr.
@return: Port number in host byte order.
*/
uint16_t mckits_inet_port(const struct sockaddr* addr);

#ifdef __cplusplus
}
#endif

#endif
