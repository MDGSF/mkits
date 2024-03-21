#ifndef MKITS_APPS_CALC24POINT_NET_BYTEBUFFER_H_
#define MKITS_APPS_CALC24POINT_NET_BYTEBUFFER_H_

#include <string>

class ByteBuffer {
 public:
  ByteBuffer();
  virtual ~ByteBuffer();

  ByteBuffer(const ByteBuffer&) = default;
  ByteBuffer& operator=(const ByteBuffer&) = default;

  ByteBuffer(ByteBuffer&&) = default;
  ByteBuffer& operator=(ByteBuffer&&) = default;

 public:
  operator const char*() const;

  void append(const char* buf, int buf_len);

  void retrieve(std::string& out_buf, int buf_len = 0);

  size_t retrieve(char* buf, int buf_len);

  size_t peek(char* buf, int buf_len);

  /*
  @param buf_len[in]: 0 means remove all
  */
  void erase(int buf_len = 0);

  int remaining() { return internal_buf_.length(); }

  bool is_empty() { return internal_buf_.empty(); }

  void clear();

 private:
  std::string internal_buf_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_BYTEBUFFER_H_
