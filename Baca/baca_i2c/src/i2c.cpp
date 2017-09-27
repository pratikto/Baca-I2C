/*
 * i2c.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: toni
 */

#include "i2c.h"

I2Cdev::I2Cdev() {
	// TODO Auto-generated constructor stub

}

/** Read a single bit from an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to read from
* @param bitNum Bit position to read (0-7)
* @param data Container for single bit value
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Status of read operation (true = success)
*/
int I2Cdev::readBit(u8 devAddr, u8 regAddr, u8 bitNum, u8 *data) {
	u8 b;
	u8 count = readByte(devAddr, regAddr, &b);
	*data = b & (1 << bitNum);
	return count;
}

/** Read a single bit from a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to read from
* @param bitNum Bit position to read (0-15)
* @param data Container for single bit value
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Status of read operation (true = success)
*/
int I2Cdev::readBitW(u8 devAddr, u8 regAddr, u8 bitNum, uint16_t *data) {
	uint16_t b;
	u8 count = readWord(devAddr, regAddr, &b);
	*data = b & (1 << bitNum);
	return count;
}

/** Read multiple bits from an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to read from
* @param bitStart First bit position to read (0-7)
* @param length Number of bits to read (not more than 8)
* @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Status of read operation (true = success)
*/
int I2Cdev::readBits(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, u8 *data) {
	// 01101001 read byte
	// 76543210 bit numbers
	//    xxx   args: bitStart=4, length=3
	//    010   masked
	//   -> 010 shifted
//	u8 count, b;
//	if ((count = readByte(devAddr, regAddr, &b, timeout)) != 0) {
//		u8 mask = ((1 << length) - 1) << (bitStart - length + 1);
//		b &= mask;
//		b >>= (bitStart - length + 1);
//		*data = b;
//	}
//	return count;
}

/** Read multiple bits from a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to read from
* @param bitStart First bit position to read (0-15)
* @param length Number of bits to read (not more than 16)
* @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Status of read operation (1 = success, 0 = failure, -1 = timeout)
*/
int I2Cdev::readBitsW(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, uint16_t *data) {
	// 1101011001101001 read byte
	// fedcba9876543210 bit numbers
	//    xxx           args: bitStart=12, length=3
	//    010           masked
	//           -> 010 shifted
	u8 count;
	uint16_t w;
	if ((count = readWord(devAddr, regAddr, &w)) != 0) {
		uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
		w &= mask;
		w >>= (bitStart - length + 1);
		*data = w;
	}
	return count;
}

/** Read single byte from an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to read from
* @param data Container for byte value read from device
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Status of read operation (true = success)
*/
int I2Cdev::readByte(u8 devAddr, u8 regAddr, u8 *data) {
	return readBytes(devAddr, regAddr, 1, data);
}

/** Read single word from a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to read from
* @param data Container for word value read from device
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Status of read operation (true = success)
*/
int I2Cdev::readWord(u8 devAddr, u8 regAddr, uint16_t *data) {
	return readWords(devAddr, regAddr, 1, data);
}

/** Read multiple bytes from an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr First register regAddr to read from
* @param length Number of bytes to read
* @param data Buffer to store read data in
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Number of bytes read (-1 indicates failure)
*/
int I2Cdev::readBytes(u8 devAddr, u8 regAddr, u8 length, u8 *data) {
//	int Status;
//
//	u8 ReadBuffer[length]; /* Read buffer for reading a page. */
//	/*
//	 * Set the defaults.
//	 */
//	ReceiveComplete = 1;
//	/*
//	 * Start the IIC device.
//	 */
//	Status = XIic_Start(&IicInstance);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}
//	/*
//	 * Set the Global Interrupt Enable.
//	 */
//	XIic_IntrGlobalEnable(IicInstance.BaseAddress);
//	/*
//	 * Wait for AAS interrupt and completion of data reception.
//	 */
//	while ((ReceiveComplete) || (XIic_IsIicBusy(&IicInstance) == TRUE)) {
//		if (SlaveRead) {
//			XIic_SlaveRecv(&IicInstance, ReadBuffer, length);
//			SlaveRead = 0;
//		}
//		}
//
//		/*
//		 * Disable the Global Interrupt Enable.
//		 */
//		XIic_IntrGlobalDisable(IicInstance.BaseAddress);
//
//		/*
//		 * Stop the IIC device.
//		 */
//		Status = XIic_Stop(&IicInstance);
//		if (Status != XST_SUCCESS) {
//			return XST_FAILURE;
//		}
//
//		return XST_SUCCESS;
}

/** Read multiple words from a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr First register regAddr to read from
* @param length Number of words to read
* @param data Buffer to store read data in
* @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
* @return Number of words read (0 indicates failure)
*/
int I2Cdev::readWords(u8 devAddr, u8 regAddr, u8 length, uint16_t *data) {

}

/** write a single bit in an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to write to
* @param bitNum Bit position to write (0-7)
* @param value New bit value to write
* @return Status of operation (true = success)
*/
bool I2Cdev::writeBit(u8 devAddr, u8 regAddr, u8 bitNum, u8 data) {
	u8 b;
	readByte(devAddr, regAddr, &b);
	b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	return writeByte(devAddr, regAddr, b);
}

/** write a single bit in a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to write to
* @param bitNum Bit position to write (0-15)
* @param value New bit value to write
* @return Status of operation (true = success)
*/
bool I2Cdev::writeBitW(u8 devAddr, u8 regAddr, u8 bitNum, uint16_t data) {
	uint16_t w;
	readWord(devAddr, regAddr, &w);
	w = (data != 0) ? (w | (1 << bitNum)) : (w & ~(1 << bitNum));
	return writeWord(devAddr, regAddr, w);
}

/** Write multiple bits in an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to write to
* @param bitStart First bit position to write (0-7)
* @param length Number of bits to write (not more than 8)
* @param data Right-aligned value to write
* @return Status of operation (true = success)
*/
bool I2Cdev::writeBits(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, u8 data) {
	//      010 value to write
	// 76543210 bit numbers
	//    xxx   args: bitStart=4, length=3
	// 00011100 mask byte
	// 10101111 original value (sample)
	// 10100011 original & ~mask
	// 10101011 masked | value
	u8 b;
	if (readByte(devAddr, regAddr, &b) != 0) {
		u8 mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1); // shift data into correct position
		data &= mask; // zero all non-important bits in data
		b &= ~(mask); // zero all important bits in existing byte
		b |= data; // combine data with existing byte
		return writeByte(devAddr, regAddr, b);
	}
	else {
		return false;
	}
}

/** Write multiple bits in a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register regAddr to write to
* @param bitStart First bit position to write (0-15)
* @param length Number of bits to write (not more than 16)
* @param data Right-aligned value to write
* @return Status of operation (true = success)
*/
bool I2Cdev::writeBitsW(u8 devAddr, u8 regAddr, u8 bitStart, u8 length, uint16_t data) {
	//              010 value to write
	// fedcba9876543210 bit numbers
	//    xxx           args: bitStart=12, length=3
	// 0001110000000000 mask word
	// 1010111110010110 original value (sample)
	// 1010001110010110 original & ~mask
	// 1010101110010110 masked | value
	uint16_t w;
	if (readWord(devAddr, regAddr, &w) != 0) {
		uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1); // shift data into correct position
		data &= mask; // zero all non-important bits in data
		w &= ~(mask); // zero all important bits in existing word
		w |= data; // combine data with existing word
		return writeWord(devAddr, regAddr, w);
	}
	else {
		return false;
	}
}

/** Write single byte to an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register address to write to
* @param data New byte value to write
* @return Status of operation (true = success)
*/
bool I2Cdev::writeByte(u8 devAddr, u8 regAddr, u8 data) {
	return writeBytes(devAddr, regAddr, 1, &data);
}

/** Write single word to a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr Register address to write to
* @param data New word value to write
* @return Status of operation (true = success)
*/
bool I2Cdev::writeWord(u8 devAddr, u8 regAddr, uint16_t data) {
	return writeWords(devAddr, regAddr, 1, &data);
}

/** Write multiple bytes to an 8-bit device register.
* @param devAddr I2C slave device address
* @param regAddr First register address to write to
* @param length Number of bytes to write
* @param data Buffer to copy new data from
* @return Status of operation (true = success)
*/
bool I2Cdev::writeBytes(u8 devAddr, u8 regAddr, u8 length, u8* data) {

}

/** Write multiple words to a 16-bit device register.
* @param devAddr I2C slave device address
* @param regAddr First register address to write to
* @param length Number of words to write
* @param data Buffer to copy new data from
* @return Status of operation (true = success)
*/
bool I2Cdev::writeWords(u8 devAddr, u8 regAddr, u8 length, uint16_t* data) {

}

/** Default timeout value for read operations.
* Set this to 0 to disable timeout detection.
*/
uint16_t I2Cdev::readTimeout = I2CDEV_DEFAULT_READ_TIMEOUT;

//volatile u8 I2Cdev::TransmitComplete;
//volatile u8 I2Cdev::ReceiveComplete;
//volatile u8 I2Cdev::SlaveRead;
//volatile u8 I2Cdev::SlaveWrite;

/*****************************************************************************/
/**
* This function reads a buffer of bytes  when the IIC Master on the bus writes
* data to the slave device.
*
* @param	BufferPtr contains the address of the data buffer to be filled.
* @param	ByteCount contains the number of bytes in the buffer to be read.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None
*
******************************************************************************/
int I2Cdev::SlaveReadData(u8 *BufferPtr, u16 ByteCount)
{
	int Status;

	/*
	 * Set the defaults.
	 */
	ReceiveComplete = 1;

	/*
	 * Start the IIC device.
	 */
	Status = XIic_Start(&IicInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the Global Interrupt Enable.
	 */
	XIic_IntrGlobalEnable(IicInstance.BaseAddress);

	/*
	 * Wait for AAS interrupt and completion of data reception.
	 */
	while ((ReceiveComplete) || (XIic_IsIicBusy(&IicInstance) == TRUE)) {
		if (SlaveRead) {
			XIic_SlaveRecv(&IicInstance, ReadBuffer, RECEIVE_COUNT);
			SlaveRead = 0;
		}
	}

	/*
	 * Disable the Global Interrupt Enable.
	 */
	XIic_IntrGlobalDisable(IicInstance.BaseAddress);

	/*
	 * Stop the IIC device.
	 */
	Status = XIic_Stop(&IicInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
* This function writes a buffer of bytes to the IIC bus when the IIC master
* initiates a read operation.
*
* @param	ByteCount contains the number of bytes in the buffer to be
*		written.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int I2Cdev::SlaveWriteData(u16 ByteCount)
{
	int Status;

	/*
	 * Set the defaults.
	 */
	TransmitComplete = 1;

	/*
	 * Start the IIC device.
	 */
	Status = XIic_Start(&IicInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the Global Interrupt Enable.
	 */
	XIic_IntrGlobalEnable(IicInstance.BaseAddress);

	/*
	 * Wait for AAS interrupt and transmission to complete.
	 */
	while ((TransmitComplete) || (XIic_IsIicBusy(&IicInstance) == TRUE)) {
		if (SlaveWrite) {
			XIic_SlaveSend(&IicInstance, WriteBuffer, SEND_COUNT);
			SlaveWrite = 0;
		}
	}

	/*
	 * Disable the Global Interrupt Enable bit.
	 */
	XIic_IntrGlobalDisable(IicInstance.BaseAddress);

	/*
	 * Stop the IIC device.
	 */
	Status = XIic_Stop(&IicInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

/****************************************************************************/
/**
* This Status handler is called asynchronously from an interrupt context and
* indicates the events that have occurred.
*
* @param	InstancePtr is not used, but contains a pointer to the IIC
* 		device driver instance which the handler is being called for.
* @param	Event indicates whether it is a request for a write or read.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void I2Cdev::StatusHandler(XIic *InstancePtr, int Event)
{
	/*
	 * Check whether the Event is to write or read the data from the slave.
	 */
	if (Event == XII_MASTER_WRITE_EVENT) {
		/*
		 * Its a Write request from Master.
		 */
		SlaveRead = 1;
	} else {
		/*
		 * Its a Read request from the master.
		 */
		SlaveWrite = 1;
	}
}

/****************************************************************************/
/**
* This Send handler is called asynchronously from an interrupt
* context and indicates that data in the specified buffer has been sent.
*
* @param	InstancePtr is a pointer to the IIC driver instance for which
*		the handler is being called for.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void I2Cdev::SendHandler(XIic *InstancePtr)
{
	TransmitComplete = 0;
}

/****************************************************************************/
/**
* This Receive handler is called asynchronously from an interrupt
* context and indicates that data in the specified buffer has been Received.
*
* @param	InstancePtr is a pointer to the IIC driver instance for which
* 		the handler is being called for.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void I2Cdev::ReceiveHandler(XIic *InstancePtr)
{
	ReceiveComplete = 0;
}

/****************************************************************************/
/**
* This function setups the interrupt system so interrupts can occur for the
* IIC. The function is application-specific since the actual system may or
* may not have an interrupt controller. The IIC device could be directly
* connected to a processor without an interrupt controller. The user should
* modify this function to fit the application.
*
* @param	IicInstPtr contains a pointer to the instance of the IIC  which
*		is going to be connected to the interrupt controller.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None.
*
****************************************************************************/
int I2Cdev::SetupInterruptSystem(XIic * IicInstPtr)
{
	int Status;

	if (InterruptController.IsStarted == XIL_COMPONENT_IS_STARTED) {
		return XST_SUCCESS;
	}

	/*
	 * Initialize the interrupt controller driver so that it's ready to use.
	 */
	Status = XIntc_Initialize(&InterruptController, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above
	 * performs the specific interrupt processing for the device.
	 */
	Status = XIntc_Connect(&InterruptController, IIC_INTR_ID,
				   (XInterruptHandler) XIic_InterruptHandler,
				   IicInstPtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the interrupt controller so interrupts are enabled for all
	 * devices that cause interrupts.
	 */
	Status = XIntc_Start(&InterruptController, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupts for the IIC device.
	 */
	XIntc_Enable(&InterruptController, IIC_INTR_ID);

	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				 (Xil_ExceptionHandler) XIntc_InterruptHandler,
				 &InterruptController);

	/*
	 * Enable non-critical exceptions.
	 */
	Xil_ExceptionEnable();


	return XST_SUCCESS;
}

I2Cdev::~I2Cdev() {
	// TODO Auto-generated destructor stub
}

