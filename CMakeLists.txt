cmake_minimum_required(VERSION 3.15)

project(TrimbleCodeChallenge)

add_executable(parser SuspectParameterNumberParser.cpp main.cpp SuspectParameterNumber.cpp CANMessage.cpp CANIdentifier.cpp AsciiCANLogInterface.cpp)