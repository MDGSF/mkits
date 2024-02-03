/*
little endian:
 Most Significant Byte(MSB), in higher memory address.
 Least Significant Byte(LSB), in lower memory address.
big endian:
 Most Significant Byte(MSB), in lower memory address.
 Least Significant Byte(LSB), in higher memory address.

example:

num = 0x12345678

little endian:
addr： 0x100   0x101   0x102   0x103
data：  0x78    0x56    0x34    0x12

big endian:
addr： 0x100   0x101   0x102   0x103
data：  0x12    0x34    0x56    0x78
*/
#ifndef MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENDIAN_H_
#define MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENDIAN_H_

#include <arpa/inet.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Check if the system is little endian.
@return:
  1: is little endian.
  0: is big endian.
*/
int mckits_is_little_endian();

/*
@brief: Check if the system is big endian.
@return:
  1: is big endian.
  0: is littel endian.
*/
int mckits_is_big_endian();

/*
@brief: host byte order to network byte order.
@param v[in]: host byte order number
@param b[out]: network byte order
*/
void mckits_host_to_net_u16(uint16_t v, uint8_t* b);

/*
@brief: network byte order to host byte order.
@param b[in]: network byte order
@return: host byte order number
*/
uint16_t mckits_net_to_host_u16(const uint8_t* b);

/*
@brief: host byte order to network byte order.
@param v[in]: host byte order number
@param b[out]: network byte order
*/
void mckits_host_to_net_u32(uint32_t v, uint8_t* b);

/*
@brief: network byte order to host byte order.
@param b[in]: network byte order
@return: host byte order number
*/
uint32_t mckits_net_to_host_u32(const uint8_t* b);

/*
@brief: host byte order to network byte order.
@param v[in]: host byte order number
@param b[out]: network byte order
*/
void mckits_host_to_net_u64(uint64_t v, uint8_t* b);

/*
@brief: network byte order to host byte order.
@param b[in]: network byte order
@return: host byte order number
*/
uint64_t mckits_net_to_host_u64(const uint8_t* b);

/*
uint16_t htons(uint16_t hostshort);  // host byte order to network byte order.
uint16_t ntohs(uint16_t netshort);  // network byte order to host byte order.
uint32_t htonl(uint32_t hostlong);  // host byte order to network byte order.
uint32_t ntohl(uint32_t netlong);  // network byte order to host byte order.
*/
#define mckits_hton_u16 htons
#define mckits_ntoh_u16 ntohs
#define mckits_hton_u32 htonl
#define mckits_ntoh_u32 ntohl

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENDIAN_H_
