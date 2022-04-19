/*******************************************************************************
** @file       CANMessage.cpp
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "CANMessage.h"

#include <cstring>
#include <cstddef>

using namespace std;

/* Exported Data -------------------------------------------------------------*/

/* Static Class Member Initialization ----------------------------------------*/

/* Class Constructors --------------------------------------------------------*/
CANMessageClass::CANMessageClass(uint32_t aTimestamp, uint8_t aCANChannel, uint32_t aRawIdentifier, uint8_t *apRawData, uint8_t aRawDataLength) :
  mIdentifier(aRawIdentifier),
  mTimestamp_us(aTimestamp),
  mLength(aRawDataLength),
  mCANChannel(aCANChannel)
{
	memset(mData, 0, sizeof(mData));

	if ((aRawDataLength <= MAX_CAN_MESSAGE_LENGTH) && (nullptr != apRawData))
	{
		memcpy(mData, apRawData, aRawDataLength);
	}
}

/* Class Destructor ----------------------------------------------------------*/
CANMessageClass::~CANMessageClass()
{
}

/* Public Class Methods ------------------------------------------------------*/
uint32_t CANMessageClass::GetDataLength() const
{
	return mLength;
}

uint8_t CANMessageClass::GetCANChannel() const
{
	return mCANChannel;
}

uint8_t CANMessageClass::GetDestinationAddress() const
{
	return mIdentifier.GetDestinationAddress();
}

uint32_t CANMessageClass::GetParameterGroupNumber() const
{
	return mIdentifier.GetParameterGroupNumber();
}

uint32_t CANMessageClass::GetRawIdentifier() const
{
	return mIdentifier.GetIdentifier();
}

uint8_t CANMessageClass::GetSourceAddress() const
{
	return mIdentifier.GetSourceAddress();
}

uint32_t CANMessageClass::GetTimestamp() const
{
	return mTimestamp_us;
}

bool CANMessageClass::GetIsMessageValid() const
{
	return mIdentifier.GetIsValid();
}

bool CANMessageClass::GetData(std::uint8_t *&apBuffer)
{
	bool retVal = GetIsMessageValid();

	if (true == retVal)
	{
		apBuffer = static_cast<uint8_t *>(mData);
	}
	else
	{
		apBuffer = nullptr;
	}
	return retVal;
}

bool CANMessageClass::GetData(std::uint8_t *apBuffer, std::uint32_t aMaxBufferLength) const
{
	bool retVal = GetIsMessageValid();

	if (GetDataLength() > aMaxBufferLength)
	{
		retVal = false;
	}
	else if (true == retVal)
	{
		memcpy(apBuffer, mData, GetDataLength());
	}
	return retVal;
}

/* Private Static Class Methods ----------------------------------------------*/

/* Private Class Methods -----------------------------------------------------*/
