/*******************************************************************************
** @file       AsciiCANLogInterface.cpp
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "AsciiCANLogInterface.h"

#include <algorithm>
#include <sstream>

using namespace std;

/* Exported Data -------------------------------------------------------------*/

/* Static Class Member Initialization ----------------------------------------*/

/* Class Constructors --------------------------------------------------------*/
AsciiCANLogInterfaceClass::AsciiCANLogInterfaceClass(string aFilePath)
{
	mFile.open(aFilePath, ios::in);
}

/* Class Destructor ----------------------------------------------------------*/
AsciiCANLogInterfaceClass::~AsciiCANLogInterfaceClass()
{
	if (true == mFile.is_open())
	{
		mFile.close();
	}
}

/* Public Class Methods ------------------------------------------------------*/
bool AsciiCANLogInterfaceClass::GetIsEndOfFile()
{
	bool retVal = false;

	if ((true == mFile.eof()) || (false == mFile.is_open()))
	{
		retVal = true;
	}
	return retVal;
}

CANMessageClass AsciiCANLogInterfaceClass::GetNextCANMessage()
{
	string lLine;
	string lDirection;
	string lTempString;
	float lTimestamp = 0.0f;
	uint32_t lIdentifier = 0;
	uint32_t lDataLength = 0;
	uint8_t lData[CANMessageClass::MAX_CAN_MESSAGE_LENGTH] = { 0 };
	uint8_t lChannel = 0;

	if (true == mFile.is_open())
	{
		while (getline(mFile, lLine) && (false == cleanLineCheckValid(lLine)))
			;

		if (false == mFile.eof())
		{
			stringstream lStringStream(lLine);
			uint16_t lByte;
			char lTempChar;

			lStringStream >> lTimestamp;
			lStringStream >> lTempString;
			lChannel = atoi(lTempString.c_str());
			lStringStream >> hex >> lIdentifier;
			CANIdentifierClass lTempIdentifier(lIdentifier);

			if (CANIdentifierClass::IT_EXTENDED == lTempIdentifier.GetIdentifierType())
			{
				lStringStream >> lTempChar; // Strip the 'x' which implies "extended ID"
			}

			lStringStream >> lDirection;
			lStringStream >> lTempChar;
			lStringStream >> lDataLength;

			for (uint32_t i = 0; ((i < lDataLength) && (i < CANMessageClass::MAX_CAN_MESSAGE_LENGTH)); i++)
			{
				lStringStream >> lTempString;
				stringstream(lTempString) >> hex >> lByte;
				lData[i] = (lByte & 0xFF);
			}
		}
	}
	return CANMessageClass(static_cast<uint32_t>(lTimestamp * 1000000), lChannel, lIdentifier, lData, lDataLength);
}

/* Private Static Class Methods ----------------------------------------------*/

/* Private Class Methods -----------------------------------------------------*/
bool AsciiCANLogInterfaceClass::cleanLineCheckValid(string &aString)
{
	bool retVal = false;

	while ((0 != aString.size()) && (0 != isspace(aString.front())))
	{
		aString.erase(aString.begin()); // Trim leading whitespace
	}

	if ((string::npos == aString.find("date")) &&
	    (string::npos == aString.find("base")) &&
	    (string::npos == aString.find("version")) &&
	    (string::npos == aString.find("events")))
	{
		retVal = true;
	}
	return retVal;
}
