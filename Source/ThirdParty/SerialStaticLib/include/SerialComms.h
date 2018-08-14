#ifndef SERIALPORT_H
#define SERIALPORT_H

#define COM_WAIT_TIME 100
#define MIN_DATA_LENGTH 32
#define MAX_DATA_LENGTH 1024

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <mutex>
#include <queue>

class SerialPort
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;

	std::thread readThread;
	std::thread writeThread;
	bool terminateReadThread = false;
	bool terminateWriteThread = false;

	int digitalValueCount = 16;
	int analogueValueCount = 8;

	std::map<int, bool> digitalValuesSinceLastUpdate;
	std::map<int, bool> digitalValues;
	std::map<int, int> analogueValues;

	std::queue<std::string> writeQueue;
	std::queue<char> readChars;
	std::mutex digitalValuesLock;
	std::mutex digitalValuesSinceLastUpdateLock;
	std::mutex analogueValuesLock;

	bool foundFirstNewLine = false;

	int readSerialPort(char *buffer, unsigned int buf_size);
	bool writeSerialPort(const char *buffer, size_t buf_size);

	void processReadBuffer(std::string inputBufferString);
	bool findNewLine(char *incomingData, int dataLength, int &newlinePos);
	void readThreadTask();
	void writeThreadTask();
	void enqueueData(char *incomingData, int dataStartPos, int dataLength);
public:
	SerialPort(int digitalCount = 16, int analogueCount = 8);
	~SerialPort();

	bool openSerialPort(const char *portName, DWORD baudrate = CBR_115200, BYTE byteSize = 8, BYTE stopbits = ONESTOPBIT, BYTE parity = NOPARITY, DWORD fDtrControl = DTR_CONTROL_ENABLE);
	bool openSerialPort(int portNumber);
	bool closeSerialPort();
	
	int getQueueSize();
	void startReading();
	void stopReading();
	void startWriting();
	void stopWriting();

	bool getDigitalValue(int valueIndex, bool sinceLastUpdate = false);
	int getAnalogueValue(int valueIndex);

	void sendCharacters(const char *sendValue);

	int getAnalogueValueCount();
	int getDigitalValueCount();

	bool isConnected();

	bool update();
};

bool isNumeric(const std::string& str);
#endif // SERIALPORT_H
