#ifndef FILTERED_COMBO_HPP
#define FILTERED_COMBO_HPP

#include "imgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream> //only used for debugging

namespace ImGui{
    bool FilteredCombo(const char *label, int *currentItem, std::vector<std::string> data,  int itemsCount, const char *filter);
}

#endif