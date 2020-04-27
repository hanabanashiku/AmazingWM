#pragma once
#include<map>

using namespace std;

namespace AmazingWM {
	/// <summary> A container object for managing keybinds.</summary>
    class Hotkeys  {
    public:
        Hotkeys();
        ~Hotkeys();

		/// <summary> Get the mod key.</summary>
		/// <returns> The virtual key that signals a command keybind.</returns>
        WORD getModKey();

		/// <summary>Set the mod key.</summary>
		/// <params name="key">The virtual key to set as the new mod key.</params>
        void setModKey(WORD key);

		/// <summary>Set a keybind. </summary>
		/// <params name="keybind">The keybind to set.</params>
		/// <params name="keys">A vector of keys to be pressed at the same time, not including the mod key.</params>
        void setKeybind(Keybinds keybind, vector<WORD> keys);

		/// <summary>Get the keys, excluding the mod key, that are associated with an action.</summary>
		/// <params name="keybind>The keybind to get.</params>
        vector<WORD> getKeybind(Keybinds keybind);

		/// <summary>Determine whether the set of keys constitute a keybind command.</summary>
		/// <params name="keys">The list of keys that were pressed.</params>
		/// <returns>They keybind associated with the keys, or Keybinds.NULL.</returns>
        Keybinds existsAsKeybind(vector<WORD> keys);

		/// <summary>Reset all keybinds and the mod key to the default setting.</summary>
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
}
