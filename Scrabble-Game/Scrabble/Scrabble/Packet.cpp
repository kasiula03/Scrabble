#include "Packet.h"
#include <sstream>

using namespace std;

Packet::Packet(string data, string type)
{
	this->data = data;
	setPacketType(type);
}
string Packet::LetterToString(Letter * letter)
{
	string tempData;
	tempData += to_string(letter->getPositionX()) + " " + to_string(letter->getPositionY());
	tempData += " " + to_string(letter->id);
	return tempData;
}
Letter Packet::StringToLetter(std::string str)
{
	std::istringstream iss(str);
	Letter temp;
	string slowo;
	iss >> slowo;
	temp.pos_x = atoi(slowo.c_str());
	iss >> slowo;
	temp.pos_y = atoi(slowo.c_str());
	iss >> slowo;
	temp.id = atoi(slowo.c_str());
	return temp;
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
Packet Packet::stringToPacket(std::string pack)
{
	Packet packet("n", "n");
	int i = 0;
	bool good = false;
	for (; i < pack.length(); i++)
	{
		if (pack[i] == '\n')
		{
			good = true;
			break;
		}
	}
	if (good)
	{
		packet.setPacketType(pack.substr(0, i));
		if (pack.length() > 0)
			packet.data = pack.substr(i + 1, pack.length());
	}
	return packet;
}
void Packet::showPacket()
{
	cout << "\nTyp: " << getPacketType() << "\t Dane: " << getData() << endl;
}