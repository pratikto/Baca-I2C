
#include <Wire.h>

#define reg0 0x0a
#define reg1 0x0b
#define reg2 0x0c
#define reg3 0x0d
#define reg4 0x0e

//uint8_t *data_receive;
//uint8_t *data_transmit;
//uint8_t regAddr;

struct sensorReg
{
	uint8_t regAddr;
	uint8_t data[2];
};

sensorReg reg[5];
uint8_t current_regAddr;

void setup() {
	//sensorReg reg[5];
	for (int i = 0; i < 5; i++)
	{
		reg[i].regAddr = 10 + i;
		reg[i].data[0] = 0;
		reg[i].data[1] = 0;
	}

	Wire.begin(8);                // join i2c bus with address #8
	Wire.onReceive(receiveEvent); // register event
	Wire.onRequest(transmitEvent); // register event
	Serial.begin(9600);           // start serial for output
}

void loop() {
	
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int numOfBytes) {
	int count = 0;
	if (numOfBytes == 1) {
		current_regAddr = Wire.read();
		Wire.endTransmission();     // stop transmitting
	}
	else
		receive_reg_data(current_regAddr);
}

void receive_reg_data(uint8_t address) {
	switch (address)
	{
		case reg0 :
			for (int i; 1 < Wire.available(); i++) {
				reg[0].data[i] = Wire.read(); // receive byte as a character
			}
			break;
		case reg1:
			for (int i; 1 < Wire.available(); i++) {
				reg[1].data[i] = Wire.read(); // receive byte as a character
			}
			break;
		case reg2:
			for (int i; 1 < Wire.available(); i++) {
				reg[2].data[i] = Wire.read(); // receive byte as a character
			}
			break;
		case reg3:
			for (int i; 1 < Wire.available(); i++) {
				reg[3].data[i] = Wire.read(); // receive byte as a character
			}
			break;
		case reg4:
			for (int i; 1 < Wire.available(); i++) {
				reg[4].data[i] = Wire.read(); // receive byte as a character
			}
			break;
		default:
			break;
	}
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void transmitEvent() {
	transmit_reg_data(current_regAddr);
}	

void transmit_reg_data(uint8_t address) {
	switch (address)
	{
	case reg0:
		Wire.write(reg[0].data, 2);
		break;
	case reg1:
		Wire.write(reg[1].data, 2);
		break;
	case reg2:
		Wire.write(reg[2].data, 2);
		break;
	case reg3:
		Wire.write(reg[3].data, 2);
		break;
	case reg4:
		Wire.write(reg[4].data, 2);
		break;
	default:
		break;
	}
}