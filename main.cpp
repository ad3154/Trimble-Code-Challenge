/*******************************************************************************
** @file       main.cpp
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "AsciiCANLogInterface.h"
#include "SuspectParameterNumberParser.h"

#include <iostream>

using namespace std;

/* Private Functions ---------------------------------------------------------*/
int main(int aNumberArguments, char *aCommandLineArguments[])
{
	uint32_t retVal = 1;

	if (3 == aNumberArguments)
	{
		AsciiCANLogInterfaceClass lLogParser(aCommandLineArguments[1]);
		SuspectParameterNumberParserClass lSPNParser(aCommandLineArguments[2]);

		lSPNParser.AddSuspectParameterNumberFilter(SuspectParameterNumberClass::SPN_AXLE_LOCATION);
		lSPNParser.AddSuspectParameterNumberFilter(SuspectParameterNumberClass::SPN_ACTUAL_INNER_WHEEL_STEERING_ANGLE);
		lSPNParser.AddSuspectParameterNumberFilter(SuspectParameterNumberClass::SPN_STATUS_OF_STEERING_AXLE);

		while (false == lLogParser.GetIsEndOfFile())
		{
			CANMessageClass lCANMessage = lLogParser.GetNextCANMessage();
			lSPNParser.ParseFilteredMessageToLog(lCANMessage);
		}
		retVal = 0;
	}
	else
	{
		cout << "Invalid Arguments" << endl;
		cout << "Format: ./<program> [input file path] [output file path]" << endl;
	}
	return retVal;
}
