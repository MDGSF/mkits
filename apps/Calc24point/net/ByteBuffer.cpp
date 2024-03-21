#include "net/ByteBuffer.h"

ByteBuffer::ByteBuffer() {}

ByteBuffer::~ByteBuffer() {}

ByteBuffer::operator const char*() const { return internal_buf_.c_str(); }

void ByteBuffer::append(const char* buf, int buf_len) {
  internal_buf_.append(buf, buf_len);
}

void ByteBuffer::retrieve(std::string& out_buf, int buf_len) {
  if (buf_len == 0 || buf_len >= internal_buf_.length()) {
    out_buf = std::move(internal_buf_);
    return;
  }

  out_buf = internal_buf_.substr(0, buf_len);
  internal_buf_.erase(0, buf_len);
}

size_t ByteBuffer::retrieve(char* buf, int buf_len) {
  if (buf_len <= 0) {
    return 0;
  }

  if (buf_len >= internal_buf_.length()) {
    buf_len = internal_buf_.length();
  }

  memcpy(buf, internal_buf_.c_str(), buf_len);
  internal_buf_.erase(0, buf_len);

  return buf_len;
}

size_t ByteBuffer::peek(char* buf, int buf_len) {
  if (buf_len <= 0) {
    return 0;
  }

  if (buf_len >= internal_buf_.length()) {
    buf_len = internal_buf_.length();
  }

  memcpy(buf, internal_buf_.c_str(), buf_len);

  return buf_len;
}

void ByteBuffer::erase(int buf_len /*= 0*/) {
  if (buf_len == 0 || buf_len >= internal_buf_.length()) {
    internal_buf_.clear();
    return;
  }
  internal_buf_.erase(0, buf_len);
}

void ByteBuffer::clear() { internal_buf_.clear(); }
