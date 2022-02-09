/*******************************************************************************
** @file       AsciiCANLogInterface.h
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/
#pragma once

/* Includes ------------------------------------------------------------------*/
#include <cstdint>

/* Local Forward Declarations ------------------------------------------------*/

/* Exported Constants --------------------------------------------------------*/

/* Exported Types ------------------------------------------------------------*/

/* Exported Classes ----------------------------------------------------------*/
class CANIdentifierClass
{
public:
	enum CAN_PRIORITY_ENUM
	{
		CP_HIGHEST_0 = 0,
		CP_1 = 1,
		CP_2 = 2,
		CP_3 = 3,
		CP_4 = 4,
		CP_5 = 5,
		CP_DEFAULT_6 = 6,
		CP_LOWEST_7 = 7
	};

	enum IDENTIFIER_TYPE_ENUM
	{
		IT_STANDARD = 0,
		IT_EXTENDED = 1
	};

	explicit CANIdentifierClass(std::uint32_t aRawIdentifierData);
	~CANIdentifierClass();

	std::uint32_t GetIdentifier() const;

	IDENTIFIER_TYPE_ENUM GetIdentifierType() const;

	std::uint32_t GetParameterGroupNumber() const;

	CAN_PRIORITY_ENUM GetPriority() const;

	std::uint8_t GetDestinationAddress() const;

	std::uint8_t GetSourceAddress() const;

	bool GetIsValid() const;

	static const std::uint32_t IDENTIFIER_TYPE_BIT_MASK = 0x80000000;
	static const std::uint32_t UNDEFINED_PARAMETER_GROUP_NUMBER = 0xFFFFFFFF;
	static const std::uint8_t GLOBAL_ADDRESS = 0xFF;
	static const std::uint8_t NULL_ADDRESS = 0xFE;

private:
	static const std::uint32_t BROADCAST_PGN_MASK = 0x0003FFFF;
	static const std::uint32_t DESTINATION_SPECIFIC_PGN_MASK = 0x0003FF00;
	static const std::uint32_t PDU2_FORMAT_MASK = 0x00F00000;

	std::uint32_t mRawIdentifier;
};
