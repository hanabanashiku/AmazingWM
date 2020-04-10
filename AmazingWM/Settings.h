#pragma once
#include "Hotkeys.h";
#include<string>

using namespace std;

class Settings
{
public:
	Settings();
	~Settings();
	Hotkeys* getHotkeys();
	static Settings* getInstance();
	string getTerminalCommand();
	void setTerminalCommand(string cmd);
private:
	static Settings *instance_;
	Hotkeys hotkeys_;
	string terminal_command_;
};