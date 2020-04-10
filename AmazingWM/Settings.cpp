#include "pch.h"
#include "Settings.h"


Settings::Settings()
{
	instance_ = this;
}


Settings::~Settings()
{
	instance_ = NULL;
}

Hotkeys* Settings::getHotkeys()
{
	return &hotkeys_;
}

Settings * Settings::getInstance()
{
	return instance_;
}

string Settings::getTerminalCommand()
{
	return terminal_command_;
}

void Settings::setTerminalCommand(string cmd)
{
	terminal_command_ = cmd;
}
