#pragma once
#include <string>

class Packet
{
	std::string data;
	std::string packetType;
public:
	Packet(std::string data, std::string type);
	Packet();

	std::string PacketToString();
	static Packet stringToPacket(std::string);
	std::string getData();
	void setData(std::string);
	void setPacketType(std::string);
	std::string getPacketType();

};