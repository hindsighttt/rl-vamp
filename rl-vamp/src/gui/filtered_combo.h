#pragma once

#include "../../lib/imgui/imgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream> //only used for debugging

namespace ImGui {
    bool FilteredCombo(const char *label, int *currentItem, std::vector<std::string> const &data,  int itemsCount, const char *filter);
}