#pragma once

#include "Word.h"
#include <cstring>

class Packet
{
	std::string data;
	std::string packetType;
public:
	Packet(std::string data, std::string type);

	static std::string LetterToString(Letter *);
	static Letter StringToLetter(std::string);
	std::string PacketToString();
	static Packet stringToPacket(std::string);
	std::string getData();
	void setPacketType(std::string);
	std::string getPacketType();
	
	void showPacket();
};