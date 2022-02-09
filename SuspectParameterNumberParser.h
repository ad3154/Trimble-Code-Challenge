/*******************************************************************************
** @file       SuspectParameterNumberParser.h
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/
#pragma once

/* Includes ------------------------------------------------------------------*/
#include "CANMessage.h"
#include "SuspectParameterNumber.h"

#include <fstream>
#include <list>
#include <string>

/* Local Forward Declarations ------------------------------------------------*/

/* Exported Constants --------------------------------------------------------*/

/* Exported Types ------------------------------------------------------------*/

/* Exported Classes ----------------------------------------------------------*/
class SuspectParameterNumberParserClass
{
public:
	enum PARAMETER_GROUP_NUMBER_ENUM
	{
		PGN_ELECTRONIC_STEERING_CONTROL = 0x00F00B
	};

	explicit SuspectParameterNumberParserClass(std::string aOutputFilePath);
	~SuspectParameterNumberParserClass();

	void AddSuspectParameterNumberFilter(
	  SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN);

	bool ParseFilteredMessageToLog(CANMessageClass &apCANMessage);

	static bool GetIsSuspectParameterNumberChildOfParameterGroupNumber(PARAMETER_GROUP_NUMBER_ENUM aPGN, SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN);

private:
	uint32_t extractRawSuspectParameterNumberData(CANMessageClass &apCANMessage, SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN);
	std::list<SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM> mFilterList;
	std::ofstream mFile;
};

/* Exported Functions --------------------------------------------------------*/

/* Exported Data -------------------------------------------------------------*/
