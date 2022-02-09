/*******************************************************************************
** @file       AsciiCANLogInterface.h
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/
#pragma once

/* Includes ------------------------------------------------------------------*/
#include <fstream>
#include <string>
#include "CANMessage.h"

/* Local Forward Declarations ------------------------------------------------*/

/* Exported Constants --------------------------------------------------------*/

/* Exported Types ------------------------------------------------------------*/

/* Exported Classes ----------------------------------------------------------*/
class AsciiCANLogInterfaceClass
{
public:
	explicit AsciiCANLogInterfaceClass(std::string aFilePath);
	~AsciiCANLogInterfaceClass();

	bool GetIsEndOfFile();

	CANMessageClass GetNextCANMessage();

private:
	bool cleanLineCheckValid(std::string &aString);
	std::ifstream mFile;
};
