/*******************************************************************************
** @file       CANIdentifier.cpp
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "CANIdentifier.h"

using namespace std;

/* Exported Data -------------------------------------------------------------*/

/* Static Class Member Initialization ----------------------------------------*/

/* Class Constructors --------------------------------------------------------*/
CANIdentifierClass::CANIdentifierClass(std::uint32_t aRawIdentifierData) :
	mRawIdentifier(aRawIdentifierData)
{
}

/* Class Destructor ----------------------------------------------------------*/
CANIdentifierClass::~CANIdentifierClass()
{
}

/* Public Class Methods ------------------------------------------------------*/
CANIdentifierClass::CAN_PRIORITY_ENUM CANIdentifierClass::GetPriority() const
{
	const uint8_t EXTENDED_IDENTIFIER_MASK = 0x07;
	const uint8_t PRIORITY_DATA_BIT_OFFSET = 26;

	CAN_PRIORITY_ENUM retVal;

	if (IT_EXTENDED == GetIdentifierType())
	{
		retVal = static_cast<CAN_PRIORITY_ENUM>((mRawIdentifier >> PRIORITY_DATA_BIT_OFFSET) & EXTENDED_IDENTIFIER_MASK);
	}
	else
	{
		retVal = CP_HIGHEST_0;
	}
	return retVal;
}

uint32_t CANIdentifierClass::GetIdentifier() const
{
	return (mRawIdentifier & (~IDENTIFIER_TYPE_BIT_MASK));
}

CANIdentifierClass::IDENTIFIER_TYPE_ENUM CANIdentifierClass::GetIdentifierType() const
{
	const uint32_t STANDARD_ID_11_BIT_SIZE = 0x7FF;
	IDENTIFIER_TYPE_ENUM retVal;

	if (mRawIdentifier <= STANDARD_ID_11_BIT_SIZE)
	{
		retVal = IT_STANDARD;
	}
	else
	{
		retVal = IT_EXTENDED;
	}
	return retVal;
}

uint32_t CANIdentifierClass::GetParameterGroupNumber() const
{
	const uint8_t PARAMTER_GROUP_NUMBER_OFFSET = 8;
	uint32_t retVal = UNDEFINED_PARAMETER_GROUP_NUMBER;

	if (IT_EXTENDED == GetIdentifierType())
	{
		if ((PDU2_FORMAT_MASK & mRawIdentifier) < PDU2_FORMAT_MASK)
		{
			retVal = ((mRawIdentifier >> PARAMTER_GROUP_NUMBER_OFFSET) & DESTINATION_SPECIFIC_PGN_MASK);
		}
		else
		{
			retVal = ((mRawIdentifier >> PARAMTER_GROUP_NUMBER_OFFSET) & BROADCAST_PGN_MASK);
		}
	}
	return retVal;
}

uint8_t CANIdentifierClass::GetDestinationAddress() const
{
	const uint8_t ADDRESS_BITS_SIZE = 0xFF;
	const uint8_t ADDRESS_DATA_OFFSET = 8;

	uint8_t retVal = GLOBAL_ADDRESS;

	if ((CANIdentifierClass::IT_EXTENDED == GetIdentifierType()) &&
		((PDU2_FORMAT_MASK & mRawIdentifier) < PDU2_FORMAT_MASK))
	{
		retVal = ((mRawIdentifier >> ADDRESS_DATA_OFFSET) & ADDRESS_BITS_SIZE);
	}
	return retVal;
}

uint8_t CANIdentifierClass::GetSourceAddress() const
{
	const uint8_t ADDRESS_BITS_SIZE = 0xFF;
	uint8_t retVal = CANIdentifierClass::GLOBAL_ADDRESS;

	if (CANIdentifierClass::IT_EXTENDED == GetIdentifierType())
	{
		retVal = (mRawIdentifier & ADDRESS_BITS_SIZE);
	}
	return retVal;
}

bool CANIdentifierClass::GetIsValid() const
{
	const uint32_t EXTENDED_ID_29_BIT_SIZE = 0x1FFFFFFF;
	const uint32_t STANDARD_ID_11_BIT_SIZE = 0x7FF;
	bool retVal;

	if (IT_EXTENDED == GetIdentifierType())
	{
		retVal = (mRawIdentifier <= EXTENDED_ID_29_BIT_SIZE);
	}
	else
	{
		retVal = (mRawIdentifier <= STANDARD_ID_11_BIT_SIZE);
	}
	return retVal;
}

/* Private Static Class Methods ----------------------------------------------*/

/* Private Class Methods -----------------------------------------------------*/
