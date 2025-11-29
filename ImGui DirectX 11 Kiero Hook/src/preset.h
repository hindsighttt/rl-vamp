#ifndef PRESET_H
# define PRESET_H

#include "cars.h"
#include "hooks.h"
#include "GUI.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace PRESET {
	void FindExistingPresets();
	void SavePreset(std::string presetName, std::vector<Item> itemVector);
	void LoadPreset(std::string presetName);
	extern std::vector<std::string> presetList;
}

#endif // !PRESET_H
