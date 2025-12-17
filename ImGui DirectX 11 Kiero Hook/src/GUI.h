#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "filtered_combo.h"
#include "hooks.h"

#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include <string>


namespace GUI
{
	void ApplyStyle();
	void Render();

	extern int selectedCarIndex;
	extern int selectedWheelsIndex;
	extern int selectedBoostIndex;
	extern int selectedTopperIndex;
	extern int selectedAntennaIndex;
	extern int selectedGoalIndex;
	extern int selectedDecalIndex;
}