#pragma once
#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_dx11.h"
#include "Renderer.h"
#include "filtered_combo.h"
#include "../game/hooks.h"
#include "../game/cars.h"
#include "../misc/preset.h"

#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include <string>
#include <iostream>

typedef struct {
	std::string title;
	std::string message;
	float duration;
	float startTime;
} Notification;

namespace GUI
{
	void ApplyStyle();
	void Render();
	void StartupAnimation();
	void DrawNotification(std::vector<Notification>& notifications);
	void AddNotification(std::string title, std::string message, float duration, std::vector<Notification>& notifications);

	extern int selectedCarIndex;
	extern int selectedWheelsIndex;
	extern int selectedBoostIndex;
	extern int selectedTopperIndex;
	extern int selectedAntennaIndex;
	extern int selectedGoalIndex;
	extern int selectedDecalIndex;
	extern float statusBarHeight;
	extern std::vector<Notification> notifications;
}