
#ifndef AXI_TRANSACTION_TIMER_H
#define AXI_TRANSACTION_TIMER_H


#ifdef __cplusplus
extern "C" {
#endif

/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG0_OFFSET 0
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG1_OFFSET 4
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG2_OFFSET 8
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG3_OFFSET 12
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG4_OFFSET 16
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG5_OFFSET 20
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG6_OFFSET 24
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG7_OFFSET 28
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG8_OFFSET 32
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG9_OFFSET 36
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG10_OFFSET 40
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG11_OFFSET 44
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG12_OFFSET 48
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG13_OFFSET 52
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG14_OFFSET 56
#define AXI_TRANSACTION_TIMER_S00_AXI_SLV_REG15_OFFSET 60


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a AXI_TRANSACTION_TIMER register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the AXI_TRANSACTION_TIMERdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void AXI_TRANSACTION_TIMER_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define AXI_TRANSACTION_TIMER_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a AXI_TRANSACTION_TIMER register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the AXI_TRANSACTION_TIMER device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 AXI_TRANSACTION_TIMER_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define AXI_TRANSACTION_TIMER_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))


#define AXI_TRANSACTION_TIMER_STATUS_OFFSET_REG     0x00
#define AXI_TRANSACTION_TIMER_TIME_OFFSET_REG       0x04
#define AXI_TRANSACTION_TIMER_START_OFFSET_REG      0x08
#define AXI_TRANSACTION_TIMER_STOP_OFFSET_REG       0x0C


/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the AXI_TRANSACTION_TIMER instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus AXI_TRANSACTION_TIMER_Reg_SelfTest(void * baseaddr_p);

/**
 * @brief Enables transaction timer at dev_addr
 * 
 * @param dev_addr Transaction timer base address
 * @return XStatus Always XST_SUCCESS
 */
XStatus AXI_transaction_timer_enable(u32 dev_addr);

/**
 * @brief Disables transaction timer at dev_addr
 * 
 * @param dev_addr Transaction timer base address
 * @return XStatus Always XST_SUCCESS
 */
XStatus AXI_transaction_timer_disable(u32 dev_addr)

/**
 * @brief Get Status register from transaction timer
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 Status reg contents
 */
u32 AXI_transaction_timer_getStatus(u32 dev_addr);

/**
 * @brief Get current count in transaction timer
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 Transaction timer last count
 */
u32 AXI_transaction_timer_getTime(u32 dev_addr);

/**
 * @brief Read the address used for starting to count
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 Start address
 */
u32 AXI_transaction_timer_getStartAddr(u32 dev_addr);

/**
 * @brief Read the address used for stoping the count
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 Stop address
 */
u32 AXI_transaction_timer_getStopAddr(u32 dev_addr);

/**
 * @brief Check if the IP is busy
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 
 *      - 0 if the IP is IDLE.
 *      - 1 if the IP is counting or looking for the given start address
 */
u32 AXI_transaction_timer_isBusy(u32 dev_addr);

/**
 * @brief Check if the IP is waiting for a start address
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 
 *      - 1 if the IP is enabled but doesn't yet detect the start address
 *      - 0 any other case
 */
u32 AXI_transaction_timer_isWaiting(u32 dev_addr);

/**
 * @brief Check if the IP counter has an overflow
 * 
 * @param dev_addr Transaction timer base address
 * @return u32 
 *      - 1 if an overflow ocurred 
 */
u32 AXI_transaction_timer_isOverflowed(u32 dev_addr);

/**
 * @brief Check if the count register was written by the counter.
 * 
 * @param dev_addr Transaction timer base address
 * @return u32
 *      - 1 if the counter value is valid
 */
u32 AXI_transaction_timer_isValid(u32 dev_addr);

/**
 * @brief Sets an address to check for start counting.
 * 
 * @param dev_addr Transaction timer base address
 * @param addr New start address
 * @return XStatus Always XST_SUCCESS
 */
XStatus AXI_transaction_timer_setStartAddr(u32 dev_addr, u32 addr);

/**
 * @brief Sets an address to check and stop the count.
 * 
 * @param dev_addr Transaction timer base address
 * @param addr New stop address
 * @return XStatus Always XST_SUCCESS
 */
XStatus AXI_transaction_timer_setStopAddr(u32 dev_addr, u32 addr);

#ifdef __cplusplus
}
#endif

#endif // AXI_TRANSACTION_TIMER_H
