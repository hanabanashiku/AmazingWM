#include "pch.h"
#include "Settings.h"
#include<sstream>
#include<cstdlib>

using namespace std;

namespace AmazingWM {
        Settings::Settings()
        {
			hotkeys_ = Hotkeys();
			readSettings();
            instance_ = this;
        }


        Settings::~Settings()
        {
			writeSettings();
            instance_ = nullptr;
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

		void Settings::writeSettings() {
			WritePrivateProfileStringA("General", "TerminalCommand", terminal_command_.c_str(), FILE);

			// save modkey
			auto hotkeys = getHotkeys();
			WritePrivateProfileStringA("Keys", "ModKey", to_string(hotkeys->getModKey()).c_str(), FILE);

			// save keybinds
			for (int i = Keybinds::kShowKeyBinds; i != Keybinds::kToggleTagViewNine; ++i) {
				auto kb = static_cast<Keybinds>(i);
				auto value = hotkeys->getKeybind(kb);
				std::ostringstream oss;

				for (auto w : value) {
					oss << w << '; ';
				}

				WritePrivateProfileStringA("Keys", to_string(i).c_str(), oss.str().c_str(), FILE);
			}
		}

		const WORD SIZE = 1024;
		bool Settings::readSettings() {
			char *str = (char*)malloc(SIZE * sizeof(char));

			try {
				terminal_command_ = getStringFromIni("General", "TerminalCommand", str);

				hotkeys_.setModKey(getKeybindKeyFromIni("Keys", "ModKey", str));

				// grab keybinds
				for (int i = Keybinds::kShowKeyBinds; i != Keybinds::kToggleClientTagNine; ++i) {

					auto key_value = getStringFromIni("Keys", to_string(i).c_str(), str);
					vector<WORD> keys = vector<WORD>();

					// split keys and push them back
					for (string j : splitString(key_value, "; ")) {
						auto k = atoll(j.c_str());
						keys.push_back(k);
					}

					// set the keybind
					hotkeys_.setKeybind(static_cast<Keybinds>(i), keys);
				}
				
				if (errno == 0x2) {
					free(str);
					return false;
				}
			}
			catch (exception& e) {
				free(str);
				return false;
			}

			free(str);
			return true;
		}

		void Settings::setDefaults() {
			terminal_command_ = "cmd";
			hotkeys_.setDefaults();
		}

		WORD Settings::getKeybindKeyFromIni(const char* section, const char* key, char* buf) {

			// n is the number of characters copied to the buffer, not including \0
			auto n = GetPrivateProfileStringA(section, key, NULL, buf, SIZE, FILE);
			if (n < 0)
				throw exception();

			char** end = &buf + n;
			WORD ret = strtoul(buf, end, 10);
			return ret;
		}

		string Settings::getStringFromIni(const char* section, const char* key, char* buf) {
			auto n = GetPrivateProfileStringA(section, key, NULL, buf, SIZE, FILE);

			if (n < 0)
				throw exception();

			return string(buf);
		}

		vector<string> splitString(string str, string del) {
			size_t pos = 0;
			string token;
			vector<string> out = vector<string>();

			while ((pos = str.find(del)) != string::npos) {
				token = str.substr(0, pos);
				out.push_back(token);
				str.erase(0, pos + del.length());
			}

			return out;
		}
}
