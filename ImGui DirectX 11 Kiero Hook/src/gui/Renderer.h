#ifndef RENDERER_H
# define RENDERER_H

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_dx11.h"
#include <cmath>

namespace Renderer { // this is not the game rendering and doesn't interact with it
	const ImVec2 GetScreenSize();
	const ImVec2 NormalizePoint(ImVec2 const &point);
	const ImVec2 DenormalizePoint(ImVec2 const &point);
	const ImVec2 World2Screen(ImVec4 const &point); // w var isn't used
	void DrawPixel(ImVec2 const& point, ImColor color);
}

#endif // !RENDERER_H