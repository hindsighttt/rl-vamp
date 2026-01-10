#include "Renderer.h"

const ImVec2 Renderer::GetScreenSize() {
	return (ImGui::GetIO().DisplaySize);
}

const ImVec2 Renderer::NormalizePoint(ImVec2 const& point) {
	ImVec2 normalized;
	ImVec2 screenSize = Renderer::GetScreenSize();

	normalized.x = 2.0f * (point.x / screenSize.x) - 1.0f;
	normalized.y = 1.0f - 2.0f * (point.y / screenSize.y);
	return (normalized);
}

const ImVec2 Renderer::DenormalizePoint(ImVec2 const& point)
{
	ImVec2 screenSpace;
	ImVec2 screenSize = Renderer::GetScreenSize();

	screenSpace.x = (point.x + 1.0f) * 0.5f * screenSize.x;
	screenSpace.y = (1.0f - point.y) * 0.5f * screenSize.y;

	return screenSpace;
}


const ImVec2 Renderer::World2Screen(ImVec4 const& point) {
	ImVec2 finalPosition;

	finalPosition.x = point.x / point.z;
	finalPosition.y = point.y / point.z;
	return (finalPosition);
}

void Renderer::DrawPixel(ImVec2 const& point, ImColor const color) {
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	drawList->AddRectFilled(point, ImVec2(point.x + 1, point.y + 1), color);
}
