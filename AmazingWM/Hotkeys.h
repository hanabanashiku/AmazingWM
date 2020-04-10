#pragma once
#include<Windows.h>
#include<map>
#include<vector>

using namespace std;

class Hotkeys
{
public:
	Hotkeys();
	~Hotkeys();
	WORD getModKey();
	void setModKey(WORD key);
	void setKeybind(Keybinds keybind, vector<WORD> keys);
	vector<WORD> getKeybind(Keybinds keybind);
	Keybinds existsAsKeybind(vector<WORD> keys);
	void setDefaults();

private:
	WORD mod_key_;
	map<Keybinds, vector<WORD>> keybinds_;
};

enum Keybinds {
	// Window manager control
	kShowKeyBinds,
	kRestartAwesome,
	kQuitAwesome,
	kRunPrompt,
	kRunInlinePrompt,
	kSpawnTerminal,
	kOpenMainMenu,

	//Clients
	kMaximizeClient,
	kMinimizeClient,
	kRestoreClient,
	kClientFullscreen,
	kKillClient,
	kClientOnTop,

	// Navigation
	kFocusNextClient,
	kFocusPreviousClient,
	kFocusFirstUrgentClient,
	kViewPreviousTag,
	kViewNextTag,
	kSwitchTagOne,
	kSwitchTagTwo,
	kSwitchTagThree,
	kSwitchTagFour,
	kSwitchTagFive,
	kSwitchTagSix,
	kSwitchTagSeven,
	kSwitchTagEight,
	kSwitchTagNine,
	kFocusNextScreen,
	kFocusPreviousScreen,
	kFocusPreviousTagSet,

	// Layout Modification
	kSwapClientWithNext,
	kSwapClientWithPrevious,
	kSendClientToNextScreen,
	kDecreaseMasterWidth,
	kIncreaseMasterWidth,
	kDecreaseMasterWindowCount,
	kIncreaseMasterWindowCount,
	kDecreaseColumns,
	kIncreaseColumns,
	kNextLayout,
	kPreviousLayout,
	kToggleClientFloat,
	kSwapClientWithMaster,
	kToggleClientTagOne,
	kToggleClientTagTwo,
	kToggleClientTagThree,
	kToggleClientTagFour,
	kToggleClientTagFive,
	kToggleClientTagSix,
	kToggleClientTagSeven,
	kToggleClientTagEight,
	kToggleClientTagNine,
	kTagClientOne,
	kTagClientTwo,
	kTagClientThree,
	kTagClientFour,
	kTagClientFive,
	kTagClientSix,
	kTagClientSeven,
	kTagClientEight,
	kTagClientNine,
	kToggleTagViewOne,
	kToggleTagViewTwo,
	kToggleTagViewThree,
	kToggleTagViewFour,
	kToggleTagViewFive,
	kToggleTagViewSix,
	kToggleTagViewSeven,
	kToggleTagViewEight,
	kToggleTagViewNine,

	// null
	Null = -1
};
