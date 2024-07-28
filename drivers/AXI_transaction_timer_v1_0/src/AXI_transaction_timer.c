

/***************************** Include Files *******************************/
#include "AXI_transaction_timer.h"

/************************** Function Definitions ***************************/


XStatus AXI_transaction_timer_enable(u32 dev_addr)
{
    AXI_TRANSACTION_TIMER_mWriteReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG, 0x00000001);
    return XST_SUCCESS;
}

XStatus AXI_transaction_timer_disable(u32 dev_addr)
{
    AXI_TRANSACTION_TIMER_mWriteReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG, 0x00000000);
    return XST_SUCCESS;
}

u32 AXI_transaction_timer_getStatus(u32 dev_addr)
{
    return AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG);
}

u32 AXI_transaction_timer_getTime(u32 dev_addr)
{
    if (!AXI_transaction_timer_isValid(dev_addr))
    {
        return 0xffffffff;
    }
    return AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_TIME_OFFSET_REG);
}

u32 AXI_transaction_timer_getStartAddr(u32 dev_addr)
{
    return AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_START_OFFSET_REG);
}

u32 AXI_transaction_timer_getStopAddr(u32 dev_addr)
{
    return AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_STOP_OFFSET_REG);
}

u32 AXI_transaction_timer_isBusy(u32 dev_addr)
{
    u32 status;
    status = AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG);
    return (status >> 1) & 0x00000001;
}

u32 AXI_transaction_timer_isWaiting(u32 dev_addr)
{
    u32 status;
    status = AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG);
    return (status >> 2) & 0x00000001;
}

u32 AXI_transaction_timer_isValid(u32 dev_addr)
{
    u32 status;
    status = AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG);
    return (status >> 3) & 0x00000001;
}

u32 AXI_transaction_timer_isOverflowed(u32 dev_addr)
{
    u32 status;
    status = AXI_TRANSACTION_TIMER_mReadReg(dev_addr, AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG);
    return (status >> 4) & 0x00000001;
}

XStatus AXI_transaction_timer_setStartAddr(u32 dev_addr, u32 addr)
{
    AXI_TRANSACTION_TIMER_mWriteReg(dev_addr, AXI_TRANSACTION_TIMER_START_OFFSET_REG, addr);
    return XST_SUCCESS;
}

XStatus AXI_transaction_timer_setStopAddr(u32 dev_addr, u32 addr)
{
    AXI_TRANSACTION_TIMER_mWriteReg(dev_addr, AXI_TRANSACTION_TIMER_STOP_OFFSET_REG, addr);
    return XST_SUCCESS;
}
