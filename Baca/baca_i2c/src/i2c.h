/*
 * i2c.h
 *
 *  Created on: Sep 26, 2017
 *      Author: toni
 */

#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#include "xparameters.h"
#include "xiic.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xil_printf.h"

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define IIC_DEVICE_ID		XPAR_IIC_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID
#define IIC_INTR_ID		XPAR_INTC_0_IIC_0_VEC_ID

/*
 * The following constant defines the address of the IIC device on the IIC bus.
 * Since the address is only 7 bits, this constant is the address divided by 2.
 */
#define SLAVE_ADDRESS		0x70	/* 0xE0 as an 8 bit number. */

#define RECEIVE_COUNT		25
#define SEND_COUNT		25

// 1000ms default read timeout (modify with "I2Cdev::readTimeout = [ms];")
#define I2CDEV_DEFAULT_READ_TIMEOUT     1000

/************************** Variable Definitions *****************************/

XIic IicInstance;		/* The instance of the IIC device. */
XIntc InterruptController;	/* The instance of the Interrupt Controller */


class I2Cdev {
public:
	I2Cdev();

	static int readBit(u8 devAddr, u8 regAddr, u8 bitNum, u8 *data);
	static int readBitW(u8 devAddr, u8 regAddr, u8 bitNum, uint16_t *data);
	static int readBits(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, u8 *data);
	static int readBitsW(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, uint16_t *data);
	static int readByte(u8 devAddr, u8 regAddr, u8 *data);
	static int readWord(u8 devAddr, u8 regAddr, uint16_t *data);
	static int readBytes(u8 devAddr, u8 regAddr, u8 length, u8 *data);
	static int readWords(u8 devAddr, u8 regAddr, u8 length, uint16_t *data);

	static bool writeBit(u8 devAddr, u8 regAddr, u8 bitNum, u8 data);
	static bool writeBitW(u8 devAddr, u8 regAddr, u8 bitNum, uint16_t data);
	static bool writeBits(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, u8 data);
	static bool writeBitsW(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, uint16_t data);
	static bool writeByte(u8 devAddr, u8 regAddr, u8 data);
	static bool writeWord(u8 devAddr, u8 regAddr, uint16_t data);
	static bool writeBytes(u8 devAddr, u8 regAddr, u8 length, u8 *data);
	static bool writeWords(u8 devAddr, u8 regAddr, u8 length, uint16_t *data);


	static uint16_t readTimeout;
	virtual ~I2Cdev();

private:
	volatile u8 TransmitComplete;
	volatile u8 ReceiveComplete;
	volatile u8 SlaveRead;
	volatile u8 SlaveWrite;
	u8 WriteBuffer[SEND_COUNT];	/* Write buffer for writing a page. */
	u8 ReadBuffer[RECEIVE_COUNT]; /* Read buffer for reading a page. */

	//axi iic act as slave
	int SlaveWriteData(u16 ByteCount);
	int SlaveReadData(u8 *BufferPtr, u16 ByteCount);
	int SetupInterruptSystem(XIic * IicInstPtr);
	void StatusHandler(XIic *InstancePtr, int Event);
	void SendHandler(XIic *InstancePtr);
	void ReceiveHandler(XIic *InstancePtr);
};

#endif /* SRC_I2C_H_ */
