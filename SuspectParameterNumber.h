/*******************************************************************************
** @file       SuspectParameterNumber.h
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
class SuspectParameterNumberClass
{
public:
	enum SUSPECT_PARAMETER_NUMBER_ENUM
	{
		SPN_WHEEL_BASED_SPEED = 0x54,
		SPN_NAVIGATION_BASED_VEHICLE_SPEED = 0x205,
		SPN_STEERABLE_LIFT_AXLE_LOWERING_INHIBIT = 0xB6A,
		SPN_STATUS_OF_STEERING_AXLE = 0xB6B,
		SPN_STEERING_TYPE = 0xB6C,
		SPN_TYPE_OF_STEERING_FORCES = 0xB6D,
		SPN_TYPE_OF_STEERING_TRANSMISSION = 0xB6E,
		SPN_ACTUAL_INNER_WHEEL_STEERING_ANGLE = 0xB6F,
		SPN_AXLE_LOCATION = 0xB70,

		SPN_NA = 0xFFFFFFFF
	};

	SuspectParameterNumberClass(SUSPECT_PARAMETER_NUMBER_ENUM aSPN, std::uint32_t aRawValue);
	~SuspectParameterNumberClass();

	std::uint32_t GetRawValue() const;

	float GetScaledValue() const;

	float GetScaleFactor() const;

	std::int32_t GetOffset() const;

	SUSPECT_PARAMETER_NUMBER_ENUM GetSuspectParameterNumber() const;

private:
	SUSPECT_PARAMETER_NUMBER_ENUM mSuspectParameterNumber;
	std::uint32_t mRawValue;
};

/* Exported Functions --------------------------------------------------------*/

/* Exported Data -------------------------------------------------------------*/
