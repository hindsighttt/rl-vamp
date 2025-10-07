#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "hooks.h"

#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include <string>


namespace GUI
{
	void ApplyStyle();
	void Render();
}