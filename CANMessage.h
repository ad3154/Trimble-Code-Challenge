/*******************************************************************************
** @file       CANMessage.h
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/
#pragma once

/* Includes ------------------------------------------------------------------*/
#include "CANIdentifier.h"

#include <cstdint>

/* Local Forward Declarations ------------------------------------------------*/

/* Exported Constants --------------------------------------------------------*/

/* Exported Types ------------------------------------------------------------*/

/* Exported Classes ----------------------------------------------------------*/
class CANMessageClass
{
public:
	CANMessageClass(std::uint32_t aTimestamp, std::uint8_t aCANChannel, std::uint32_t aRawIdentifier, std::uint8_t *apRawData, std::uint8_t aRawDataLength);

	~CANMessageClass();

	std::uint32_t GetDataLength() const;
	std::uint8_t GetCANChannel() const;
	std::uint8_t GetDestinationAddress() const;
	std::uint32_t GetParameterGroupNumber() const;
	std::uint32_t GetRawIdentifier() const;
	std::uint8_t GetSourceAddress() const;
	std::uint32_t GetTimestamp() const;

	bool GetIsMessageValid() const;

	bool GetData(std::uint8_t *&apBuffer);
	bool GetData(std::uint8_t *apBuffer, std::uint32_t aMaxBufferLength) const;

	static const std::uint8_t MAX_CAN_MESSAGE_LENGTH = 8;

private:
	CANIdentifierClass mIdentifier;
	std::uint32_t mTimestamp_us;
	std::uint8_t mData[MAX_CAN_MESSAGE_LENGTH];
	std::uint8_t mLength;
	std::uint8_t mCANChannel;
};

/* Exported Functions --------------------------------------------------------*/

/* Exported Data -------------------------------------------------------------*/
