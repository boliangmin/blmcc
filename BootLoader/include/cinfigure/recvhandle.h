#ifndef __RECVHANDLE_H
#define __RECVHANDLE_H

#include "sys.h"

#define POSITIVE_RESPONSE 0x0521U
#define NEGATIVE_RESPONSE 0x0721U

#define TEST_RESPONSE 38

void CanRecvService(void);
void SendPositiveResponse(u16 buff[]);
void SendNagetiveResponse(u16 buff[]);

#endif
