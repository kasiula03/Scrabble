#include "Packet.h"

using namespace std;

Packet::Packet()
{
	Packet("n", "n");
}
Packet::Packet(string data, string type)
{
	this->data = data;
	setPacketType(type);
}
void Packet::setPacketType(string type)
{
	this->packetType = type;
}
string Packet::getPacketType()
{
	return this->packetType;
}
string Packet::PacketToString()
{
	string strPacket;
	strPacket += getPacketType() + "\n" + this->data;
	return strPacket;
}
string Packet::getData()
{
	return this->data;
}
void Packet::setData(std::string data)
{
	this->data = data;
}
Packet Packet::stringToPacket(std::string pack)
{
	Packet packet("n", "n");
	int i = 0;
	for (; i < pack.length(); i++)
	{
		if (pack[i] == '\n')
			break;
	}
	packet.setPacketType(pack.substr(0, i));
	if(pack.length() > 0)
		packet.data = pack.substr(i + 1, pack.length());
	return packet;
}