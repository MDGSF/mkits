#ifndef MKITS_APPS_CALC24POINT_NET_EVENT_LOOP_H_
#define MKITS_APPS_CALC24POINT_NET_EVENT_LOOP_H_

#include <memory>

#include "net/IOMultiplex.h"

enum class IOMultiplexType {
  IOMultiplexTypeSelect,
  IOMultiplexTypePoll,
  IOMultiplexTypeEpoll,
};

/*
@brief: 事件循环，每个 EventLoop 里面都有一个 epoll/poll/select。
  1. 可以注册事件到 EventLoop 中。
  2. 事件触发后，回调函数会被调用。
*/
class EventLoop final {
 public:
  EventLoop();
  virtual ~EventLoop();

  EventLoop(const EventLoop&) = delete;
  EventLoop& operator=(const EventLoop&) = delete;

  EventLoop(EventLoop&&) = delete;
  EventLoop& operator=(EventLoop&&) = delete;

 public:
  /*
  @brief: 初始化 EventLoop。
  @return: 0 mean success, else means error.
  */
  int init(IOMultiplexType iotype = IOMultiplexType::IOMultiplexTypeEpoll);

  /*
  @brief: EventLoop loop forever until EventLoop stoped.
  */
  void run();

  /*
  @brief: 注册一个 read 事件到 EventLoop 中。
  @param fd[in]: 要注册的文件描述符。
  @param event_dispatcher[in]: fd 对应的事件处理者，比如 Acceptor 和
    TCPConnection.
  @param read_event[in]:
    true 注册 read 事件。
    false 取消 read 事件。
  */
  void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                           bool read_event);

  /*
  @brief: 注册一个 write 事件到 EventLoop 中。
  @param fd[in]: 要注册的文件描述符。
  @param event_dispatcher[in]: fd 对应的事件处理者，比如 Acceptor 和
    TCPConnection.
  @param write_event[in]:
    true 注册 write 事件。
    false 取消 write 事件。
  */
  void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                            bool write_event);

  void unregister_read_event(int fd, IEventDispatcher* event_dispatcher,
                             bool read_event);
  void unregister_write_event(int fd, IEventDispatcher* event_dispatcher,
                              bool write_event);
  void unregister_all_event(int fd, IEventDispatcher* event_dispatcher);

 private:
  bool running_{true};
  std::unique_ptr<IOMultiplex> io_multiplex_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_EVENT_LOOP_H_
