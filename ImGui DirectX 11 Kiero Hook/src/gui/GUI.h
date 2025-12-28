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


namespace GUI
{
	void ApplyStyle();
	void Render();
	void StartupAnimation(bool &startupAnimation);

	extern int selectedCarIndex;
	extern int selectedWheelsIndex;
	extern int selectedBoostIndex;
	extern int selectedTopperIndex;
	extern int selectedAntennaIndex;
	extern int selectedGoalIndex;
	extern int selectedDecalIndex;
	extern float statusBarHeight;
}