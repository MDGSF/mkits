#ifndef MKITS_APPS_CALC24POINT_NET_IEVENTDISPATCHER_H_
#define MKITS_APPS_CALC24POINT_NET_IEVENTDISPATCHER_H_

class IEventDispatcher {
 public:
  virtual void on_read() = 0;
  virtual void on_write() = 0;
  virtual void on_close() = 0;
  virtual void enable_read(bool read) = 0;
  virtual void enable_write(bool write) = 0;
};

#endif  // MKITS_APPS_CALC24POINT_NET_IEVENTDISPATCHER_H_
