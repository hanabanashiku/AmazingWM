#pragma once
#include "Hotkeys.h";
#include<string>

using namespace std;

namespace AmazingWM {
	/// <summary> Manages persistant application-wide settings. </summary>
    class Settings  {
    public:
        Settings();
        ~Settings();

		/// <summary> Get the keybind configuration.</summary>
		/// <returns> The current Hotkeys instance.</returns>
        Hotkeys* getHotkeys();

		/// <summary> Get the settings singleton.</summary>
		/// <returns>The current Settings instance.</summary>
        static Settings* getInstance();

		/// <summary>Resets all settings to the default state.</summary>
		void setDefaults();

		/// <summary>Gets the command to launch the terminal client.</summary>
		/// <returns>A command string.</return>
		/// <remarks>Defaults to cmd.exe</remarks>
        string getTerminalCommand();

		/// <summary>Sets the command to launch the terminal client.</summary>
		/// <params name="cmd">The new command</params>
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
