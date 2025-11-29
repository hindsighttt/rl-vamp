#include "GUI.h"
#include "cars.h"
#include "preset.h"
#include <iostream>

bool state = true;
int GUI::selectedCarIndex = 0;
int GUI::selectedWheelsIndex = 0;
int GUI::selectedBoostIndex = 0;
int GUI::selectedTopperIndex = 0;
int GUI::selectedAntennaIndex = 0;

void GUI::ApplyStyle()
{
	ImGuiStyle &style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(style.WindowPadding.x, 200);
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.ChildRounding = 12.0f;
	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 5.0f;
	style.FramePadding = ImVec2(8, 6);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 10.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(0.70196f, 0.70196f, 0.70196f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 0.20f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.40196, 0.40196, 0.40196, 1.00f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.26f, 0.28f, 0.50f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
}

static void AddCombo(const char *label, std::vector<Item> itemVector, int &selectedItem, int &hookID, const char *search)
{
	if (strlen(search) > 0)
	{
		std::vector<std::string> items;
		for (int i = 0; i < itemVector.size(); i++)
			items.push_back(itemVector[i].ingameName);
		ImGui::FilteredCombo(label, &selectedItem, items, items.size(), search);
	}
	else
	{
		std::vector<const char *> items;
		for (int i = 0; i < itemVector.size(); i++)
			items.push_back(itemVector[i].ingameName.c_str());
		ImGui::Combo(label, &selectedItem, items.data(), items.size());
	}
	hookID = itemVector[selectedItem].ingameID;
}

void GUI::Render()
{
	static std::string presetName = "";
	static std::string searchTerm = "";
	static int selectedPresetIndex = 0;
	static bool previousKeyState = GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT);

	if (!previousKeyState && (GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT)))
		state = !state;
	previousKeyState = GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT);

	if (!state)
		return;
	ImGui::Begin("rl-vamp", (bool*)0, ImGuiWindowFlags_NoCollapse);
	{
		ImGui::Checkbox("Enabled", &HOOKS::enabled);
		ImGui::InputText("Search", searchTerm.data(), searchTerm.capacity());
		ImGui::NewLine();
		AddCombo("Body", CARS::CarsList, GUI::selectedCarIndex, HOOKS::carID, searchTerm.c_str());
		AddCombo("Wheels", CARS::WheelsList, GUI::selectedWheelsIndex, HOOKS::wheelID, searchTerm.c_str());
		AddCombo("Boost", CARS::BoostsList, GUI::selectedBoostIndex, HOOKS::boostID, searchTerm.c_str());
		AddCombo("Topper", CARS::ToppersList, GUI::selectedTopperIndex, HOOKS::hatID, searchTerm.c_str());
		AddCombo("Antennas", CARS::AntennasList, GUI::selectedAntennaIndex, HOOKS::antennaID, searchTerm.c_str());

		if (ImGui::Button("Reload Items"))
		{
			CARS::CarsList.clear();
			CARS::WheelsList.clear();
			CARS::BoostsList.clear();
			CARS::ToppersList.clear();
			CARS::AntennasList.clear();

			GUI::selectedAntennaIndex = 0;
			GUI::selectedCarIndex = 0;
			GUI::selectedWheelsIndex = 0;
			GUI::selectedBoostIndex = 0;
			GUI::selectedTopperIndex = 0;
			CARS::LoadAllItems("items.csv");
		}

		ImGui::NewLine();
		std::vector<const char*> presets;
		for (int i = 0; i < PRESET::presetList.size(); i++)
			presets.push_back(PRESET::presetList[i].c_str());
		if (ImGui::Combo("Saved Presets", &selectedPresetIndex, presets.data(), presets.size()))
			presetName = PRESET::presetList[selectedPresetIndex];

		ImGui::InputText("Preset", presetName.data(), MAX_PATH);
		if (ImGui::Button("Save"))
		{
			std::vector<Item> itemList = { 
				CARS::CarsList[GUI::selectedCarIndex], 
				CARS::WheelsList[GUI::selectedWheelsIndex],
				CARS::BoostsList[GUI::selectedBoostIndex],
				CARS::ToppersList[GUI::selectedTopperIndex], 
				CARS::AntennasList[GUI::selectedAntennaIndex]
			};

			PRESET::SavePreset(presetName, itemList);
			PRESET::presetList.clear();
			PRESET::FindExistingPresets();
		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			PRESET::LoadPreset(presetName);
		}
		ImGui::SameLine();
		if (ImGui::Button("Delete"))
		{
			remove(presetName.c_str());
			PRESET::presetList.clear();
			PRESET::FindExistingPresets();
		}

		ImGui::NewLine();
		ImGui::Text("Press \"DELETE\" to hide the menu");
		ImGui::Text("Warning: Disabling the plugin in bakkesmod will close the game");
	}
	ImGui::End();
}
