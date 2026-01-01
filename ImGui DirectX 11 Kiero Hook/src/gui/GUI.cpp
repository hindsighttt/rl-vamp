#include "GUI.h"

bool state = true;
int GUI::selectedCarIndex = 0;
int GUI::selectedWheelsIndex = 0;
int GUI::selectedBoostIndex = 0;
int GUI::selectedTopperIndex = 0;
int GUI::selectedAntennaIndex = 0;
int GUI::selectedGoalIndex = 0;
int GUI::selectedDecalIndex = 0;
float GUI::statusBarHeight = 10.0f;
std::vector<Notification> GUI::notifications;

void GUI::ApplyStyle()
{
	ImGuiStyle &style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(600, 560);
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.ChildRounding = 12.0f;
	style.WindowPadding = ImVec2(15, 15);
	//style.WindowRounding = 5.0f;
	GUI::statusBarHeight = 30.0f;
	style.WindowRounding = 0.0f;
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
		if (ImGui::FilteredCombo(label, &selectedItem, items, items.size(), search)) {
			std::string title = label; title.append(" updated");
			GUI::AddNotification(title, items[selectedItem], 4.0f, GUI::notifications);
		}
	}
	else
	{
		std::vector<const char *> items;
		for (int i = 0; i < itemVector.size(); i++)
			items.push_back(itemVector[i].ingameName.c_str());
		if (ImGui::Combo(label, &selectedItem, items.data(), items.size())) {
			std::string title = label; title.append(" updated");
			GUI::AddNotification(title, items[selectedItem], 4.0f, GUI::notifications);
		}
	}
	hookID = itemVector[selectedItem].ingameID;
}

static ImVec2 AddVec2(ImVec2 source, ImVec2 add) {
	return (ImVec2(source.x + add.x, source.y + add.y));
}

static ImVec2 SubtractFloatFromVec2(ImVec2 vector, float sub) {
	ImVec2 result = vector;

	result.x -= sub;
	result.y -= sub;
	return (result);
}

static ImVec2 AddFloatToVec2(ImVec2 vector, float add) {
	ImVec2 result = vector;

	result.x += add;
	result.y += add;
	return (result);
}

static void DrawGlowingBackground(float borderSize) {
	ImGuiStyle &style = ImGui::GetStyle();
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	ImVec2 windowPosition = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();

	int maxValue = 255;
	int minValue = 0;
	float duration = 2.0f;

	float currentTime = (float)ImGui::GetTime();
	float moduloTime = fmod(currentTime, duration);
	int cycles = floor(currentTime / duration);
	bool direction = (cycles % 2) == 1;

	int brightness;
	if (direction)
		brightness = (int)std::lerp(minValue, maxValue, moduloTime / duration);
	else
		brightness = (int)std::lerp(maxValue, minValue, moduloTime / duration);
	ImVec2 startPosition = SubtractFloatFromVec2(windowPosition, borderSize);
	ImVec2 endPosition = AddFloatToVec2(AddVec2(windowPosition, windowSize), borderSize);
	drawList->AddRectFilled(startPosition, AddVec2(endPosition, ImVec2(0, GUI::statusBarHeight)), ImColor(49, 124, 245, brightness), style.WindowRounding);
}

static void DrawBackground(bool separator) {
	ImGuiStyle& style = ImGui::GetStyle();
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	ImVec2 windowPosition = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImColor backgroundColor = style.Colors[ImGuiCol_WindowBg];
	ImColor statusBarColor = style.Colors[ImGuiCol_TitleBg];
	ImColor separatorColor = style.Colors[ImGuiCol_Separator];
	ImColor textColor = style.Colors[ImGuiCol_Text];
	float circleSize = 7.0f;
	bool active = ImGui::IsWindowFocused();
	if (active)
		statusBarColor = style.Colors[ImGuiCol_TitleBgActive];
	drawList->AddRectFilled(windowPosition, AddVec2(windowPosition, windowSize), backgroundColor, style.WindowRounding);

	// status Bar code
	ImVec2 statusBarPosition = AddVec2(windowPosition, ImVec2(0, windowSize.y));
	ImVec2 statusBarSize = AddVec2(statusBarPosition, ImVec2(windowSize.x, GUI::statusBarHeight));
	drawList->AddRectFilled(statusBarPosition, statusBarSize, statusBarColor, style.WindowRounding);
	if (separator)
		drawList->AddLine(statusBarPosition, AddVec2(statusBarPosition, ImVec2(windowSize.x, 0)), separatorColor);

	// status bar circle
	int maxValue = 255;
	int minValue = 100;
	float duration = 2.0f;
	float currentTime = (float)ImGui::GetTime();
	float moduloTime = fmod(currentTime, duration);
	int cycles = floor(currentTime / duration);
	bool direction = (cycles % 2) == 1;
	int brightness;
	if (direction)
		brightness = (int)std::lerp(minValue, maxValue, moduloTime / duration);
	else
		brightness = (int)std::lerp(maxValue, minValue, moduloTime / duration);
	drawList->AddCircleFilled(ImVec2(statusBarPosition.x + circleSize * 3, statusBarPosition.y + circleSize * 2), circleSize, ImColor(49, 124, 245, brightness));

	// status bar text
	std::string text = "Ready";
	ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
	ImVec2 textPosition = AddVec2(statusBarPosition, ImVec2(textSize.x / 2 + circleSize * 3.0f, textSize.y / 2 + 1));
	drawList->AddText(textPosition, textColor, text.c_str());
}

void GUI::Render()
{
	//Notification notification{ "Item updated",
	//						"items[selectedItem]",
	//						2.0f,
	//						ImGui::GetTime() };
	//GUI::notifications.push_back(notification);

	static std::string presetName = "";
	static std::string searchTerm = "";
	static int selectedPresetIndex = 0;
	static bool previousKeyState = GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT);

	if (!previousKeyState && (GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT)))
		state = !state;
	previousKeyState = GetAsyncKeyState(VK_DELETE) || GetAsyncKeyState(VK_INSERT);

	GUI::DrawNotification(GUI::notifications);

	if (!state)
		return;

	ImGui::Begin("rl-vamp", 
				(bool*)0, 
				ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoBackground
				//| ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoScrollbar
			);
	{
		if (ImGui::Checkbox("Enabled", &HOOKS::enabled)) {
			std::string status = "Disabled";
			if (HOOKS::enabled)
				status = "Enabled";
			GUI::AddNotification("Status changed", status, 1.0f, GUI::notifications);
		}
		ImGui::InputText("Search", searchTerm.data(), searchTerm.capacity());
		ImGui::NewLine();
		AddCombo("Body", CARS::CarsList, GUI::selectedCarIndex, HOOKS::carID, searchTerm.c_str());
		AddCombo("Decal", CARS::DecalsList, GUI::selectedDecalIndex, HOOKS::decalID, searchTerm.c_str());
		AddCombo("Wheels", CARS::WheelsList, GUI::selectedWheelsIndex, HOOKS::wheelID, searchTerm.c_str());
		AddCombo("Boost", CARS::BoostsList, GUI::selectedBoostIndex, HOOKS::boostID, searchTerm.c_str());
		AddCombo("Topper", CARS::ToppersList, GUI::selectedTopperIndex, HOOKS::hatID, searchTerm.c_str());
		AddCombo("Antennas", CARS::AntennasList, GUI::selectedAntennaIndex, HOOKS::antennaID, searchTerm.c_str());
		AddCombo("Goal Explosion", CARS::GoalsList, GUI::selectedGoalIndex, HOOKS::goalExplosionID, searchTerm.c_str());

		if (ImGui::Button("Reload Items"))
		{
			CARS::CarsList.clear();
			CARS::WheelsList.clear();
			CARS::BoostsList.clear();
			CARS::ToppersList.clear();
			CARS::AntennasList.clear();
			CARS::DecalsList.clear();
			CARS::GoalsList.clear();
			CARS::ValidCars.clear();
			CARS::ValidWheels.clear();

			GUI::selectedAntennaIndex = 0;
			GUI::selectedCarIndex = 0;
			GUI::selectedWheelsIndex = 0;
			GUI::selectedBoostIndex = 0;
			GUI::selectedTopperIndex = 0;
			GUI::selectedGoalIndex = 0;
			GUI::selectedDecalIndex = 0;
			CARS::LoadAllItemsFromFile("items.csv");
			int itemCount =	CARS::CarsList.size()
							+ CARS::WheelsList.size()
							+ CARS::BoostsList.size()
							+ CARS::ToppersList.size()
							+ CARS::AntennasList.size()
							+ CARS::DecalsList.size()
							+ CARS::GoalsList.size();
			std::string message = std::to_string(itemCount) + " items found";
			GUI::AddNotification("Reload items", message, 3.0f, GUI::notifications);
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
	}
	DrawGlowingBackground(2.0f);
	DrawBackground(false);
	ImGui::End();
}

void GUI::StartupAnimation(bool &startupAnimation)
{
	double currentTime = ImGui::GetTime();
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	ImGuiIO io = ImGui::GetIO();
	float maxTime = 3.0; // in seconds
	int backgroundBrightness = 175;
	int textBrightness = 255;

	backgroundBrightness = std::lerp(backgroundBrightness, 0, currentTime / maxTime);
	textBrightness = std::lerp(textBrightness, 0, currentTime / maxTime);

	drawList->AddRectFilled(ImVec2(0, 0), io.DisplaySize, ImColor(0, 0, 0, backgroundBrightness));
	drawList->AddText(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), ImColor(255, 255, 255, textBrightness), "RL-VAMP IS LOADING");

	int barHeight = 10;
	int barLength = io.DisplaySize.x;
	barLength = std::lerp(0, barLength, currentTime / maxTime);
	drawList->AddRectFilled(ImVec2(0, 0), ImVec2(barLength, barHeight), ImColor(49, 124, 245, 255));

	if (currentTime > maxTime) {
		startupAnimation = true;
		GUI::AddNotification("rl-vamp", "rl-vamp is succesfully loaded", 5.0f, GUI::notifications);
	}
}

void GUI::DrawNotification(std::vector<Notification>& notifications)
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	ImVec2 screenSize = ImGui::GetIO().DisplaySize;
	ImGuiStyle& style = ImGui::GetStyle();
	float currentTime = ImGui::GetTime();

	// remove expired ones
	std::erase_if(notifications, [currentTime](const Notification& notification) {
		return currentTime > (notification.startTime + notification.duration);
	});

	for (int i = 0; i < notifications.size(); i++) {
		// background
		if (!notifications[i].startTime)
			notifications[i].startTime = ImGui::GetTime();
		ImVec2 startPosition = style.FramePadding;
		startPosition = AddVec2(startPosition, ImVec2(0, (100 + style.FramePadding.y) * i));
		ImVec2 size = AddVec2(startPosition, ImVec2(250, 100));
		drawList->AddRectFilled(startPosition, size, ImColor(style.Colors[ImGuiCol_WindowBg]), style.WindowRounding);

		// title bar
		ImVec2 titleBarSize = AddVec2(startPosition, ImVec2(250, 20));
		drawList->AddRectFilled(startPosition, titleBarSize, ImColor(style.Colors[ImGuiCol_TitleBgActive]));

		// title text
		ImVec2 titleSize = ImGui::CalcTextSize(notifications[i].title.c_str());
		ImVec2 titlePosition = AddVec2(startPosition, ImVec2(style.FramePadding.x, titleSize.y / 2 - style.FramePadding.y / 2));
		drawList->AddText(titlePosition, ImColor(style.Colors[ImGuiCol_Text]), notifications[i].title.c_str());

		// message
		ImVec2 messagePosition = ImVec2(startPosition.x + style.FramePadding.x, titleBarSize.y + style.FramePadding.y);
		drawList->AddText(messagePosition, ImColor(style.Colors[ImGuiCol_Text]), notifications[i].message.c_str());

		// bar
		ImVec2 barPosition = ImVec2(startPosition.x, size.y);
		ImVec2 barSize = ImVec2(size.x, size.y - 5);
		float elapsedTime = currentTime - notifications[i].startTime;
		barSize.x = std::lerp(barPosition.x, size.x, elapsedTime / notifications[i].duration);
		drawList->AddRectFilled(barPosition, barSize, ImColor(49, 124, 245, 255));
	}
}

void GUI::AddNotification(std::string title, std::string message, float duration, std::vector<Notification>& notifications) {
	Notification notification = { title, message, duration, ImGui::GetTime() };
	notifications.push_back(notification);
}
