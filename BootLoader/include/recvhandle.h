#ifndef __RECVHANDLE_H
#define __RECVHANDLE_H

#include "sys.h"

void CanRecvService(void);
void SendPositiveResponse(u8 buff[]);
void SendNagetiveResponse(u8 buff[]);

#endif
