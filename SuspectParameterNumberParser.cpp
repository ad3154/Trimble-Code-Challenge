/*******************************************************************************
** @file       SuspectParameterNumberParser.cpp
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "SuspectParameterNumberParser.h"

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

/* Exported Data -------------------------------------------------------------*/

/* Static Class Member Initialization ----------------------------------------*/

/* Class Constructors --------------------------------------------------------*/
SuspectParameterNumberParserClass::SuspectParameterNumberParserClass(
  string aOutputFilePath)
{
	mFile.open(aOutputFilePath, ios::out | ios::trunc);

	if (true == mFile.is_open())
	{
		mFile << "Timestamp,SPN(n),ScaledValue(n)," << endl;
	}
}

/* Class Destructor ----------------------------------------------------------*/
SuspectParameterNumberParserClass::~SuspectParameterNumberParserClass()
{
	while (0 != mFilterList.size())
	{
		mFilterList.erase(mFilterList.begin());
	}

	if (true == mFile.is_open())
	{
		mFile.close();
	}
}

/* Public Class Methods ------------------------------------------------------*/
void SuspectParameterNumberParserClass::AddSuspectParameterNumberFilter(SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN)
{
	mFilterList.push_back(aSPN);
}

bool SuspectParameterNumberParserClass::ParseFilteredMessageToLog(CANMessageClass &apCANMessage)
{
	vector<SuspectParameterNumberClass> lSuspectParameterNumbers;
	uint32_t lPGN = apCANMessage.GetParameterGroupNumber();
	bool retVal = false;

	for (list<SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM>::iterator i = mFilterList.begin(); i != mFilterList.end(); ++i)
	{
		if (true == GetIsSuspectParameterNumberChildOfParameterGroupNumber(static_cast<PARAMETER_GROUP_NUMBER_ENUM>(lPGN), *i))
		{
			lSuspectParameterNumbers.push_back(SuspectParameterNumberClass(*i, extractRawSuspectParameterNumberData(apCANMessage, *i)));
		}
	}

	if (0 != lSuspectParameterNumbers.size())
	{
		mFile << setprecision(10) << fixed << (static_cast<float>(apCANMessage.GetTimestamp()) / 1000000.0f) << ",";
	}

	for (uint32_t i = 0; i < lSuspectParameterNumbers.size(); i++)
	{
		mFile << lSuspectParameterNumbers[i].GetSuspectParameterNumber() << ",";
		mFile << lSuspectParameterNumbers[i].GetScaledValue() << ",";
		if (lSuspectParameterNumbers[i].GetScaledValue() > 16000)
		{
			break;
		}
	}

	if (0 != lSuspectParameterNumbers.size())
	{
		mFile << endl;
	}
	return retVal;
}

bool SuspectParameterNumberParserClass::GetIsSuspectParameterNumberChildOfParameterGroupNumber(PARAMETER_GROUP_NUMBER_ENUM aPGN, SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN)
{
	bool retVal = false;

	switch (aPGN)
	{
		case PGN_ELECTRONIC_STEERING_CONTROL:
		{
			switch (aSPN)
			{
				case SuspectParameterNumberClass::SPN_STEERABLE_LIFT_AXLE_LOWERING_INHIBIT:
				case SuspectParameterNumberClass::SPN_STEERING_TYPE:
				case SuspectParameterNumberClass::SPN_TYPE_OF_STEERING_FORCES:
				case SuspectParameterNumberClass::SPN_TYPE_OF_STEERING_TRANSMISSION:
				case SuspectParameterNumberClass::SPN_ACTUAL_INNER_WHEEL_STEERING_ANGLE:
				case SuspectParameterNumberClass::SPN_AXLE_LOCATION:
				case SuspectParameterNumberClass::SPN_STATUS_OF_STEERING_AXLE:
				{
					retVal = true;
				}
				break;

				default:
				{
				}
				break;
			}
		}
		break;

		default:
		{
		}
		break;
	}
	return retVal;
}

/* Private Static Class Methods ----------------------------------------------*/

/* Private Class Methods -----------------------------------------------------*/
uint32_t SuspectParameterNumberParserClass::extractRawSuspectParameterNumberData(CANMessageClass &apCANMessage, SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN)
{
	uint32_t retVal = 0;
	uint8_t *lpData;
	uint8_t lLength = apCANMessage.GetDataLength();

	if (true == apCANMessage.GetData(lpData))
	{
		switch (aSPN)
		{
			case SuspectParameterNumberClass::SPN_ACTUAL_INNER_WHEEL_STEERING_ANGLE:
			{
				retVal = ((static_cast<uint32_t>(lpData[1]) << 8) | (lpData[0]));
			}
			break;

			case SuspectParameterNumberClass::SPN_STATUS_OF_STEERING_AXLE:
			{
				retVal = (lpData[3] & 0x0F);
			}
			break;

			case SuspectParameterNumberClass::SPN_AXLE_LOCATION:
			{
				retVal = lpData[2];
			}
			break;

			case SuspectParameterNumberClass::SPN_STEERABLE_LIFT_AXLE_LOWERING_INHIBIT:
			{
				retVal = ((lpData[3] >> 4) & 0x03);
			}
			break;

			case SuspectParameterNumberClass::SPN_STEERING_TYPE:
			{
				retVal = (lpData[4] & 0x0F);
			}
			break;

			case SuspectParameterNumberClass::SPN_TYPE_OF_STEERING_FORCES:
			{
				retVal = ((lpData[4] >> 4) & 0x0F);
			}
			break;

			case SuspectParameterNumberClass::SPN_TYPE_OF_STEERING_TRANSMISSION:
			{
				retVal = (lpData[5] & 0x0F);
			}
			break;

			default:
			{
			}
			break;
		}
	}
	return retVal;
}
