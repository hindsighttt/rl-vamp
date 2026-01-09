#include "preset.h"

std::vector<std::string> PRESET::presetList;

static int FindItemInList(std::vector<Item> itemList, int itemId)
{
	for (int i = 0; i < itemList.size(); i++)
	{
		if (itemId == itemList[i].ingameID)
			return (i);
	}
	return (-1);
}

static std::vector<std::string> StringSplit(const std::string& input, const std::string& delimiter) {
	std::vector<std::string> tokens;
	size_t position = 0;
	size_t start = 0;
	std::string token;
	std::string str = input;

	while ((position = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, position);
		tokens.push_back(token);
		str.erase(0, position + delimiter.length());
	}
	tokens.push_back(str);
	return (tokens);
}

void PRESET::FindExistingPresets()
{
	presetList.push_back("None");
	std::string path = ".\\";
	int i = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string entryPathStr = entry.path().string();
		std::vector<std::string> splitResult = StringSplit(entryPathStr, "\\");
		std::string name = splitResult.back();
		std::string extension = StringSplit(name, ".").back();
		if (extension != name)
			continue;

		PRESET::presetList.push_back(name);
		i++;
	}
	std::cout << "[PRESET::FindExistingPresets]: Found " << i << " presets" << std::endl;
}

void PRESET::SavePreset(std::string presetName, std::vector<Item> itemVector)
{
	if (presetName == "None")
		return;
	std::ofstream presetFile(presetName);
	for (int i = 0; itemVector.size() > i; i++)
		presetFile << itemVector[i].type << ":" << itemVector[i].ingameID << std::endl;
	presetFile.close();

	std::cout << "[PRESET::SavePreset]: Saved preset: " << presetName << std::endl;
}

static void LoadParsedItem(const unsigned int itemID, std::vector<Item> &itemList, int &guiStorage, int& hookStorage) {
	hookStorage = itemID;
	int itemIndex = FindItemInList(itemList, itemID);
	if (itemIndex != -1)
		guiStorage = itemIndex;
}

void PRESET::LoadPreset(std::string presetName)
{
	std::ifstream presetFile(presetName);
	std::string lineBuffer;

	while (std::getline(presetFile, lineBuffer))
	{
		std::vector<std::string> lineData = StringSplit(lineBuffer, ":");
		std::string itemType = lineData[0];
		int itemId = std::atoi(lineData[1].c_str());

		int itemIndex;
		if (itemType == "Body")
			LoadParsedItem(itemId, CARS::CarsList, GUI::selectedCarIndex, HOOKS::carID);
		else if (itemType == "Wheels")
			LoadParsedItem(itemId, CARS::WheelsList, GUI::selectedWheelsIndex, HOOKS::wheelID);
		else if (itemType == "Boost")
			LoadParsedItem(itemId, CARS::BoostsList, GUI::selectedBoostIndex, HOOKS::boostID);
		else if (itemType == "Antenna")
			LoadParsedItem(itemId, CARS::AntennasList, GUI::selectedAntennaIndex, HOOKS::antennaID);
		else if (itemType == "Hat")
			LoadParsedItem(itemId, CARS::ToppersList, GUI::selectedTopperIndex, HOOKS::hatID);
		else if (itemType == "Skin")
			LoadParsedItem(itemId, CARS::DecalsList, GUI::selectedDecalIndex, HOOKS::decalID);
		else if (itemType == "GoalExplosion")
			LoadParsedItem(itemId, CARS::GoalsList, GUI::selectedGoalIndex, HOOKS::goalExplosionID);
	}
	presetFile.close();
	std::cout << "[PRESET::LoadPreset]: Loaded preset: " << presetName << std::endl;
}