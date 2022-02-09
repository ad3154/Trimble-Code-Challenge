/*******************************************************************************
** @file       SuspectParameterNumber.cpp
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "SuspectParameterNumber.h"

/* Exported Data -------------------------------------------------------------*/

/* Static Class Member Initialization ----------------------------------------*/

/* Class Constructors --------------------------------------------------------*/
SuspectParameterNumberClass::SuspectParameterNumberClass(SUSPECT_PARAMETER_NUMBER_ENUM aSPN, uint32_t aRawValue) :
  mSuspectParameterNumber(aSPN),
  mRawValue(aRawValue)
{
}

/* Class Destructor ----------------------------------------------------------*/
SuspectParameterNumberClass::~SuspectParameterNumberClass()
{
}

/* Public Class Methods ------------------------------------------------------*/
uint32_t SuspectParameterNumberClass::GetRawValue() const
{
	return mRawValue;
}

float SuspectParameterNumberClass::GetScaledValue() const
{
	return (static_cast<float>(mRawValue * GetScaleFactor()) + GetOffset());
}

float SuspectParameterNumberClass::GetScaleFactor() const
{
	float retVal = 0.0f;

	switch (mSuspectParameterNumber)
	{
		case SPN_ACTUAL_INNER_WHEEL_STEERING_ANGLE:
		{
			retVal = 0.00377358490566037735849056603774f;
		}
		break;

		case SPN_STEERABLE_LIFT_AXLE_LOWERING_INHIBIT:
		case SPN_STEERING_TYPE:
		case SPN_TYPE_OF_STEERING_FORCES:
		case SPN_TYPE_OF_STEERING_TRANSMISSION:
		case SPN_AXLE_LOCATION:
		case SPN_STATUS_OF_STEERING_AXLE:
		default:
		{
			retVal = 1;
		}
		break;
	}
	return retVal;
}

int32_t SuspectParameterNumberClass::GetOffset() const
{
	int32_t retVal = 0;

	switch (mSuspectParameterNumber)
	{
		case SPN_ACTUAL_INNER_WHEEL_STEERING_ANGLE:
		{
			retVal = -125;
		}
		break;

		case SPN_STEERING_TYPE:
		case SPN_TYPE_OF_STEERING_FORCES:
		case SPN_TYPE_OF_STEERING_TRANSMISSION:
		case SPN_STEERABLE_LIFT_AXLE_LOWERING_INHIBIT:
		case SPN_AXLE_LOCATION:
		case SPN_STATUS_OF_STEERING_AXLE:
		default:
		{
			retVal = 0;
		}
		break;
	}
	return retVal;
}

SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM SuspectParameterNumberClass::GetSuspectParameterNumber() const
{
	return mSuspectParameterNumber;
}

/* Private Static Class Methods ----------------------------------------------*/

/* Private Class Methods -----------------------------------------------------*/
