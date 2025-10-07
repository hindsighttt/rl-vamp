#include "GUI.h"
#include "cars.h"
#include <iostream>

bool state = true;
int selectedCarIndex = 0;
int selectedWheelsIndex = 0;
int selectedBoostIndex = 0;
int selectedTopperIndex = 0;
int selectedAntennaIndex = 0;

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

void GUI::Render()
{
	static bool previousKeyState = GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT);

	if (!previousKeyState && (GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT)))
		state = !state;
	previousKeyState = GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT);

	if (!state)
		return;
	ImGui::Begin("rl-vamp", (bool*)0, ImGuiWindowFlags_NoCollapse);
	{
		ImGui::Checkbox("Enabled", &HOOKS::enabled);

		// CARS
		std::vector<const char*> Caritems;
		for (int i = 0; i < CARS::CarsList.size(); i++)
			Caritems.push_back(CARS::CarsList[i].ingameName.c_str());
		ImGui::Combo("Body", &selectedCarIndex, Caritems.data(), Caritems.size());
		HOOKS::carID = CARS::CarsList[selectedCarIndex].ingameID;

		// Wheels
		std::vector<const char*> Wheelsitems;
		for (int i = 0; i < CARS::WheelsList.size(); i++)
				Wheelsitems.push_back(CARS::WheelsList[i].ingameName.c_str());
		ImGui::Combo("Wheels", &selectedWheelsIndex, Wheelsitems.data(), Wheelsitems.size());
		HOOKS::wheelID = CARS::WheelsList[selectedWheelsIndex].ingameID;

		// Boost
		std::vector<const char*> Boostitems;
		for (int i = 0; i < CARS::BoostsList.size(); i++)
			Boostitems.push_back(CARS::BoostsList[i].ingameName.c_str());
		ImGui::Combo("Boost", &selectedBoostIndex, Boostitems.data(), Boostitems.size());
		HOOKS::boostID = CARS::BoostsList[selectedBoostIndex].ingameID;

		// Toppers
		std::vector<const char*> TopperItems;
		for (int i = 0; i < CARS::ToppersList.size(); i++)
			TopperItems.push_back(CARS::ToppersList[i].ingameName.c_str());
		ImGui::Combo("Topper", &selectedTopperIndex, TopperItems.data(), TopperItems.size());
		HOOKS::hatID = CARS::ToppersList[selectedTopperIndex].ingameID;

		// Antennas
		std::vector<const char*> AntennaItems;
		for (int i = 0; i < CARS::AntennasList.size(); i++)
			AntennaItems.push_back(CARS::AntennasList[i].ingameName.c_str());
		ImGui::Combo("Antennas", &selectedAntennaIndex, AntennaItems.data(), AntennaItems.size());
		HOOKS::antennaID = CARS::AntennasList[selectedAntennaIndex].ingameID;

		ImGui::NewLine();
		ImGui::Text("Press \"DELETE\" to hide the menu");
		ImGui::Text("Warning: Disabling the plugin in bakkesmod will close the game");
	}
	ImGui::End();
}
