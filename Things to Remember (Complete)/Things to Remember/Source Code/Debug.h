#include <iostream>
#include <fstream>

using namespace std;

class Debug
{

private:

	static Debug *inst;

	Debug();
	~Debug();

	ofstream FILE;

	bool DisplayInfo; // Display debug info

public:

	bool DebugInfoActive()
	{
		return DisplayInfo;
	}

	void ToggleDebugInfo()
	{
		if(DisplayInfo == true)
		{
			DisplayInfo = false;
		}
		else if(DisplayInfo == false)
		{
			DisplayInfo = true;
		}
	}

	void Print(string output);

	static Debug *GetInstance();

	void DestroyInstance();


};