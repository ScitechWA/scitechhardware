#include <windows.h>

#include "stdafx.h"
#include "include\SerialComms.h"
#include <iostream>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}


SerialPort::SerialPort(int digitalCount, int analogueCount)
{
	this->connected = false;
	digitalValueCount = digitalCount;
	analogueValueCount = analogueCount;

	for (int i = 0; i < digitalValueCount + 1; i++)
	{
		digitalValuesLock.lock();
		digitalValues[i] = false;
		digitalValuesLock.unlock();
	}

	for (int i = 0; i < digitalValueCount + 1; i++)
	{
		digitalValuesSinceLastUpdateLock.lock();
		digitalValuesSinceLastUpdate[i] = false;
		digitalValuesSinceLastUpdateLock.unlock();
	}

	for (int i = 0; i < analogueValueCount + 1; i++)
	{
		analogueValuesLock.lock();
		analogueValues[i] = 0;
		analogueValuesLock.unlock();
	}
}

SerialPort::~SerialPort()
{

}

bool SerialPort::openSerialPort(int portNumber)
{
	std::string portString = "\\\\.\\COM" + std::to_string(portNumber);
	return openSerialPort(portString.c_str());
	return true;
}

bool SerialPort::openSerialPort(const char *portName, DWORD baudrate /*= CBR_115200*/, BYTE byteSize /*= 8*/, BYTE stopbits /*= ONESTOPBIT*/, BYTE parity /*= NOPARITY*/, DWORD fDtrControl /*= DTR_CONTROL_ENABLE*/)
{

	this->handler = CreateFileA(static_cast<LPCSTR>(portName),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (this->handler == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
			return false;
		}
		else
		{
			printf("ERROR!!!");
			return false;
		}
	}
	else {
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(this->handler, &dcbSerialParameters)) {
			printf("failed to get current serial parameters");
			return false;
		}
		else {
			dcbSerialParameters.BaudRate = baudrate;
			dcbSerialParameters.ByteSize = byteSize;
			dcbSerialParameters.StopBits = stopbits;
			dcbSerialParameters.Parity = parity;
			dcbSerialParameters.fDtrControl = fDtrControl;
			dcbSerialParameters.fOutX = true;
			dcbSerialParameters.fInX = true;
			dcbSerialParameters.fOutxCtsFlow = false;
			dcbSerialParameters.fOutxDsrFlow = false;
			dcbSerialParameters.fDsrSensitivity = false;
			dcbSerialParameters.fRtsControl = RTS_CONTROL_DISABLE;

			if (!SetCommState(handler, &dcbSerialParameters))
			{
				printf("ALERT: could not set Serial port parameters\n");
				return false;
			}
			else {
				this->connected = true;
				PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(COM_WAIT_TIME);
				return true;
			}
		}
	}
}

bool SerialPort::closeSerialPort()
{
	stopReading();
	stopWriting();

	if (this->connected) {
		this->connected = false;
		CloseHandle(this->handler);
	}
	return true;
}

int SerialPort::getQueueSize()
{
	if (this->connected)

	{
		ClearCommError(this->handler, &this->errors, &this->status);

		return this->status.cbInQue;

	}
	else
	{
		return 0;
	}
}

int SerialPort::readSerialPort(char *buffer, unsigned int buf_size)
{
	if (!connected) return 0;

	DWORD bytesRead;
	//unsigned int toRead = 0;

	//ClearCommError(this->handler, &this->errors, &this->status);

	//if (this->status.cbInQue > 0) {
//		if (this->status.cbInQue > buf_size) {
			//toRead = buf_size;
		//}
		//else toRead = this->status.cbInQue;
	//}


	if (ReadFile(this->handler, buffer, buf_size, &bytesRead, NULL)) return bytesRead;

	return 0;
}

bool SerialPort::writeSerialPort(const char *buffer, size_t buf_size)
{
	if (!connected) return false;

	DWORD bytesSend;

	if (!WriteFile(this->handler, (void*)buffer, buf_size, &bytesSend, 0)) {
		ClearCommError(this->handler, &this->errors, &this->status);
		return false;
	}
	else return true;
}

void SerialPort::processReadBuffer(std::string inputBufferString)
{
	try
	{
		std::vector<std::string> inputBlocks = split(inputBufferString, ' ');

		for (int i = 0; i < inputBlocks.size(); i++)
		{
			// delete empty vector inside container.
			if (inputBlocks[i].empty()) inputBlocks.erase(inputBlocks.begin() + i);
		}

		long inputBlockIndex = 0;
		char currentTypeInput = 'Z';
		bool expectTypeInput = true;
		long inputIndex = -1;
		std::string::size_type sz;

		std::string block = inputBlocks[inputBlockIndex];


		while (inputBlockIndex < inputBlocks.size())
		{
			block = inputBlocks[inputBlockIndex];
			if (expectTypeInput)
			{
				// expecting to find an 'A' or 'D' starting character
				if (block.find("A") == 0)
				{
					// found Analogue value
					std::string keyString = block.substr(1, block.length() - 1);
					if (isNumeric(keyString))
					{

						/// TODO WORK HERE
						long currentInputIndex = std::stol(keyString, &sz);

						if ((currentInputIndex > 0) && (currentInputIndex <= analogueValueCount))
						{
							inputIndex = currentInputIndex;
							expectTypeInput = false;
							currentTypeInput = 'A';
						}
					}

				}
				else if (block.find("D") == 0)
				{
					// found Digital Value
					std::string keyString = block.substr(1, block.length() - 1);
					if (isNumeric(keyString))
					{
						long currentInputIndex = std::stol(keyString, &sz);

						if ((currentInputIndex > 0) && (currentInputIndex <= digitalValueCount))
						{
							inputIndex = currentInputIndex;
							expectTypeInput = false;
							currentTypeInput = 'D';
						}
					}
				}
				inputBlockIndex++;
			}
			else
			{
				// expecting a value to associate with inputIndex;
				if (inputIndex > 0)
				{
					if (isNumeric(block))
					{
						long currentValue = std::stol(block, &sz);

						if (currentTypeInput == 'A')
						{
							//
							analogueValuesLock.lock();
							analogueValues[inputIndex] = currentValue;
							analogueValuesLock.unlock();
							expectTypeInput = true;
						}
						else if (currentTypeInput == 'D')
						{
							if (block.length() == 1)
							{
								if ((currentValue < 2) && (currentValue >= 0))
								{
									digitalValuesLock.lock();
									digitalValues[inputIndex] = currentValue;
									digitalValuesLock.unlock();
									expectTypeInput = true;
								}
							}
							else
							{
								// block length isn't 1, fail back to finding the next type block
								expectTypeInput = true;
							}
						}
					}
					else
					{
						// value block is non-numeric, fail back to finding a type block
						expectTypeInput = true;
					}
				}
				inputBlockIndex++;
			}
		}
	}
	catch (const std::exception&)
	{
		return;
	}
}

bool SerialPort::findNewLine(char *incomingData, int dataLength, int &newlinePos)
{
	bool result = false;
	newlinePos = -1;
	for (int i = 0; i < dataLength; i++)
	{
		if (incomingData[i] == '\r')
		{
			if (i + 1 < dataLength)
			{
				if (incomingData[i + 1] == '\n')
				{
					result = true;
					newlinePos = i + 2;
					return result;
				}
			}
		}
	}
	return result;
}

void SerialPort::readThreadTask()
{
	char incomingData[MAX_DATA_LENGTH];

	while (!terminateReadThread)
	{
		int queueSize = getQueueSize();
		while (getQueueSize() > MIN_DATA_LENGTH)
		{
			int readLength = queueSize;
			if (readLength > MAX_DATA_LENGTH) readLength = MAX_DATA_LENGTH;

			if (connected)
			{
				int readResult = readSerialPort(incomingData, readLength);
				if (readResult > 0)
				{

					int dataStartPos = 0;

					if (!foundFirstNewLine)
					{
						int newlinePos = 0;
						if (findNewLine(incomingData, readResult, newlinePos))
						{
							dataStartPos = newlinePos;
							foundFirstNewLine = true;
						}
					}
					enqueueData(incomingData, dataStartPos, readLength);

				}
				queueSize = getQueueSize();
			}
		}
		//Sleep(1);
	}
}

void SerialPort::writeThreadTask()
{
	while (!terminateWriteThread)
	{
		if (connected)
		{

			size_t queueSize = writeQueue.size();
			while (queueSize > 0)
			{

				std::string outString = writeQueue.front();
				const char* outgoingData = outString.c_str();

				bool writeResult = writeSerialPort(outgoingData, outString.length());

				writeQueue.pop();
				queueSize = writeQueue.size();
				Sleep(1);
			}
		}
		Sleep(10);
	}

}

void SerialPort::enqueueData(char *incomingData, int dataStartPos, int dataLength)
{
	int i = dataStartPos;
	while (i < dataLength)
	{
		if (incomingData[i] != '\r')
		{
			// not a newline, push to queue
			readChars.push(incomingData[i]);
			i++;
		}
		else
		{
			// possibly a newline character, check for next
			if ((i + 1) < dataLength)
			{
				if (incomingData[i + 1] == '\n')
				{
					// newline, process existing queue and clear;
					std::string line = "";
					while (readChars.size() > 0)
					{
						line += readChars.front();
						readChars.pop();
					}
					processReadBuffer(line);

					i += 2;
				}
			}
			else
			{
				// 
				i++;
			}
		}
	}
}


void SerialPort::startReading()
{
	terminateReadThread = false;
	readThread = std::thread(&SerialPort::readThreadTask, this);
}


void SerialPort::stopReading()
{
	terminateReadThread = true;
	if (readThread.joinable()) readThread.join();
}

void SerialPort::startWriting()
{
	terminateWriteThread = false;
	writeThread = std::thread(&SerialPort::writeThreadTask, this);
}

void SerialPort::stopWriting()
{
	terminateWriteThread = true;
	if (writeThread.joinable()) writeThread.join();
}


bool SerialPort::getDigitalValue(int valueIndex, bool sinceLastUpdate /*= false*/)
{
	if (valueIndex > digitalValueCount) return false;
	digitalValuesLock.lock();
	bool returnvalue = digitalValues[valueIndex];
	digitalValuesLock.unlock();

	if (sinceLastUpdate)
	{
		if (digitalValuesSinceLastUpdate[valueIndex])
		{
			digitalValuesSinceLastUpdateLock.lock();
			digitalValuesSinceLastUpdate[valueIndex] = digitalValues[valueIndex];
			digitalValuesSinceLastUpdateLock.unlock();
			return true;
		}
		else
		{
			return returnvalue;
		}
	}
	else return returnvalue;

}


int SerialPort::getAnalogueValue(int valueIndex)
{
	if (valueIndex > analogueValueCount) return -1;
	analogueValuesLock.lock();
	int returnValue = analogueValues[valueIndex];
	analogueValuesLock.unlock();
	return returnValue;
}

void SerialPort::sendCharacters(const char* sendValue)
{
	writeQueue.push(sendValue);
}

int SerialPort::getAnalogueValueCount()
{
	return analogueValueCount;
}

int SerialPort::getDigitalValueCount()
{
	return digitalValueCount;
}

bool SerialPort::isConnected()
{
	return this->connected;
}

bool SerialPort::update()
{
	for (int i = 0; i < digitalValueCount; i++)
	{
		digitalValuesSinceLastUpdateLock.lock();
		digitalValuesSinceLastUpdate[i] = false;
		digitalValuesSinceLastUpdateLock.unlock();
	}
	return true;
}

bool isNumeric(const std::string& str) {
	try {
		size_t sz;
		std::stol(str, &sz);
		return sz == str.size();
	}
	catch (const std::invalid_argument&) {
		// if no conversion could be performed.
		return false;
	}
	catch (const std::out_of_range&) {
		//  if the converted value would fall out of the range of the result type.
		return false;
	}
	/*
	for (int i = 0; i < (str.length() - 1); i++) {
		if ((int)str[i] < 10) {
			return true;
		}
		else {
			return false;
		}
	}
	*/

}