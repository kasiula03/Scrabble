#pragma once

#include "Packet.h"
#include "TasksQueue.h"
#include "Dictionary.h"
class Serwer;

class PacketHandler
{
public:
	PacketHandler(Serwer *);

	Dictionary * dictionary;

	Packet HandleReceiveMessage();
	TasksQueue sendQueue;
	Serwer * server;
};