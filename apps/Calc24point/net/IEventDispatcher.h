#ifndef MKITS_APPS_CALC24POINT_NET_IEVENTDISPATCHER_H_
#define MKITS_APPS_CALC24POINT_NET_IEVENTDISPATCHER_H_

/*
@brief: IEventDispatcher 会被放到 EventLoop 中去检测事件。
继承类有 Acceptor 和 TCPConnection。
  Acceptor: 用于处理 listen fd 的事件。
  TCPConnection: 用于处理每一个 client fd 的事件。
*/
class IEventDispatcher {
 public:
  /*
  @brief: 当检测到 socket 的 read 事件的时候, 也就是表示 socket
  有数据可以读取, on_read() 这个 callback 会被调用
  */
  virtual void on_read() = 0;

  /*
  @brief: 当检测到 socket 的 write 事件的时候, 也就是表示 socket
  的缓冲区未满，可以写入数据, on_write() 这个 callback 会被调用
  */
  virtual void on_write() = 0;

  /*
  @brief:
  */
  virtual void on_close() = 0;

  /*
  @brief: 开启或关闭 read 事件的检测。
  @param read[in]:
    true 表示开启 read 事件的检测。
    false 表示关闭 read 事件的检测。
  */
  virtual void enable_read(bool read) = 0;

  /*
  @brief: 开启或关闭 write 事件的检测。
  @param write[in]:
    true 表示开启 write 事件的检测。
    false 表示关闭 write 事件的检测。
  */
  virtual void enable_write(bool write) = 0;
};

#endif  // MKITS_APPS_CALC24POINT_NET_IEVENTDISPATCHER_H_
