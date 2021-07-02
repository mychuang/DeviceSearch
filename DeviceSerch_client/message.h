#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdint.h>
#include <QString>
#define MCAST_ADDR "239.255.43.21"
#define MCAST_PORT 5555
#define MCAST_MSG_MAGIC 0xABCD

struct Message{
    uint8_t from[6];
    char Model_Name[16];
    char User_Name[16];
};

#define MCAST_MSG_MAGIC 0xABCD
#define MCAST_MSG_PROBE 0x01


#endif // MESSAGE_H
