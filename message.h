#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

#define MCAST_ADDR "239.255.43.21"
#define MCAST_PORT 5555
#define MCAST_MSG_MAGIC 0xABCD

struct Message{
    uint16_t magic;
    uint8_t type;
    uint8_t reserve;
    uint8_t from[6];
    uint8_t to[6];
    uint16_t size;
    uint8_t data[1400];
};

#define MCAST_MSG_MAGIC 0xABCD
#define MCAST_MSG_PROBE 0x01

#endif // MESSAGE_H
