#include "Debug.h"

Debug *Debug::inst = 0;

Debug *Debug::GetInstance()
{
	if(inst == 0)
	{
		inst = new Debug();
	}

	return inst;
}

Debug::Debug()
{
	FILE.open("Debug.txt", ios::out | ios::trunc);
	DisplayInfo = false;
}

Debug::~Debug()
{
	FILE.close();
	DestroyInstance();
}

void Debug::Print(string output)
{
	FILE << output.c_str() << endl;

	FILE.flush();
}

void Debug::DestroyInstance()
{
	delete inst;

	inst = 0;
}