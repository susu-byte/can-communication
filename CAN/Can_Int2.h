#ifndef __CAN_Int_H
#define __CAN_Int_H
#include "defines.h"
void CAN1_Configure(void);
void mCANwrite(int _IDstd,mCANbuffer* _data,uint8_t _length) ;
                             

#endif /* CAN_MCAN_H_ */
