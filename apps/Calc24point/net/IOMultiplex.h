#ifndef MKITS_APPS_CALC24POINT_NET_IOMULTIPLEX_H_
#define MKITS_APPS_CALC24POINT_NET_IOMULTIPLEX_H_

#include <vector>

#include "net/IEventDispatcher.h"

/*
@brief: IO 多路复用。用于对 epoll, poll, select 进行封装。
*/
class IOMultiplex {
 public:
  IOMultiplex() = default;
  virtual ~IOMultiplex() = default;

  IOMultiplex(const IOMultiplex&) = delete;
  IOMultiplex& operator=(const IOMultiplex&) = delete;

  IOMultiplex(IOMultiplex&&) = default;
  IOMultiplex& operator=(IOMultiplex&&) = default;

  /*
  @brief: IO 多路复用的核心函数，用于等待事件的触发。
  @param timeout_us[in]: 等待的最长时间（微妙）。
  @param triggered_fds[in]:
  */
  virtual void poll(int timeout_us,
                    std::vector<IEventDispatcher*>& triggered_fds) = 0;

  /*
  @brief: 注册一个 read 事件。
  @param fd[in]: 要注册的文件描述符。
  @param event_dispatcher[in]: fd 对应的事件处理者，比如 Acceptor 和
    TCPConnection.
  @param read_event[in]:
    true 注册 read 事件。
    false 取消 read 事件。
  */
  virtual void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) = 0;

  /*
  @brief: 注册一个 write 事件。
  @param fd[in]: 要注册的文件描述符。
  @param event_dispatcher[in]: fd 对应的事件处理者，比如 Acceptor 和
    TCPConnection.
  @param write_event[in]:
    true 注册 write 事件。
    false 取消 write 事件。
  */
  virtual void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) = 0;

  virtual void unregister_read_event(int fd, IEventDispatcher* event_dispatcher,
                                     bool read_event) = 0;
  virtual void unregister_write_event(int fd,
                                      IEventDispatcher* event_dispatcher,
                                      bool write_event) = 0;
  virtual void unregister_read_write_event(
      int fd, IEventDispatcher* event_dispatcher) = 0;
};

#endif  // MKITS_APPS_CALC24POINT_NET_IOMULTIPLEX_H_
