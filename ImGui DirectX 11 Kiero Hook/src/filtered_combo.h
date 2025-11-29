#ifndef FILTERED_COMBO_H
#define FILTERED_COMBO_H

#include "../imgui/imgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream> //only used for debugging

namespace ImGui {
    bool FilteredCombo(const char *label, int *currentItem, std::vector<std::string> data,  int itemsCount, const char *filter);
}

#endif