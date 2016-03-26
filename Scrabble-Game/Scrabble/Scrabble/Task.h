#pragma once
#include <string>

using namespace std;

class Task
{

public:
	Task(string taskName);
	void serveTask();

	string taskName;
};