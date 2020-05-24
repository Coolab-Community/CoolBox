#include "MbTcp_Task.h"
#include "MyTask.h"

#define REG_INPUT_START 0x01
#define REG_INPUT_NREGS 60
#define REG_HOLDING_START 0x01
#define REG_HOLDING_NREGS 100

extern uint16_t adcBuffer[2]; // Buffer for store the results of the ADC conversion
extern ADC_Struct *ADCValues ; 
extern UART_HandleTypeDef huart1;
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS];
static USHORT usRegHoldingStart = REG_HOLDING_START;
static USHORT usRegHoldingBuf[REG_HOLDING_NREGS];

extern struct netif gnetif;
void User_notification(struct netif *netif);  // ETH Init Notification 

void ModbusTask(const void * argument)
{

  eMBTCPInit(502);  // init modbus stack
  eMBEnable();  // enable the ModBus   
  while(1)
  {

    usRegInputBuf[1]= (int)ADCValues->ADC_1;
    usRegInputBuf[2]= (int)ADCValues->ADC_2;
    eMBPoll();   // Polling MbTcp req
    osDelay(50);
  }
}
void User_notification(struct netif *netif)
{
  if (netif_is_up(netif))
  {
    // ETH and LwIP init success
  }
  else
  {
    //ETH and LwIP init error 
  }
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int             iRegIndex;

  if( ( usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
  {
    iRegIndex = ( int )( usAddress - usRegHoldingStart );
    switch ( eMode )
    {
    case MB_REG_READ:
      while( usNRegs > 0 )
      {
        *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
        *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
        iRegIndex++;
        usNRegs--;
      }
      break;

    case MB_REG_WRITE:
      while( usNRegs > 0 )
      {
        usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
        usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
        iRegIndex++;
        usNRegs--;
      }
    }
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  //HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

  return eStatus;
}

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int             iRegIndex;

  if( ( usAddress >= REG_INPUT_START ) && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
  {
    iRegIndex = ( int )( usAddress - usRegInputStart );
    while( usNRegs > 0 )
    {
      *pucRegBuffer++ =
        ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
      *pucRegBuffer++ =
        ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
      iRegIndex++;
      usNRegs--;
    }
  }
  else
  {
    eStatus = MB_ENOREG;
  }
  //HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
  return eStatus;
}



eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
  return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  return MB_ENOREG;
}
