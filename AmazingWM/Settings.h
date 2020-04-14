#pragma once
#include "Hotkeys.h";
#include<string>

using namespace std;

namespace AmazingWM {
    class Settings
    {
    public:
        Settings();
        ~Settings();
        Hotkeys* getHotkeys();
        static Settings* getInstance();
		void setDefaults();
        string getTerminalCommand();
        void setTerminalCommand(string cmd);
    private:
		const char* FILE = "%APPDATA%\AmazingWM\Config.ini";
        static Settings *instance_;
        Hotkeys hotkeys_;
        string terminal_command_;
		void writeSettings();
		bool readSettings();
		WORD getKeybindKeyFromIni(const char* section, const char* key, char* buf);
		string getStringFromIni(const char* section, const char* key, char* buf);
    };
}
