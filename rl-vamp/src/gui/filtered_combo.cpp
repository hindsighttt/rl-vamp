#include "filtered_combo.h"

bool ImGui::FilteredCombo(const char* label, int* currentItem, std::vector<std::string> const &data, int itemsCount, const char* filter)
{
    int dataSize = static_cast<int>(data.size());
    std::vector<const char*> filteredList;
    filteredList.reserve(dataSize);
                                                                                                                                       
    std::string filterLower;
    if (filter != nullptr)
    {
        filterLower = filter;
        std::transform(filterLower.begin(), filterLower.end(), filterLower.begin(), ::tolower);
    }

    if (!filterLower.empty())
    {
        for (int i = 0; i < dataSize; i++)
        {
            std::string currentEntry = data[i];
            std::transform(currentEntry.begin(), currentEntry.end(), currentEntry.begin(), ::tolower);

            if (currentEntry.find(filterLower) != std::string::npos)
                filteredList.push_back(data[i].c_str());
        }
    }
    else
    {
        for (int i = 0; i < dataSize; i++)
            filteredList.push_back(data[i].c_str());
    }

    int currentFilteredItem = 0;
    if (filterLower.empty())
        currentFilteredItem = *currentItem;

    int filteredCount = static_cast<int>(filteredList.size());
    bool status = ImGui::Combo(label, &currentFilteredItem, filteredList.data(), filteredCount);

    if (status)
    {
        std::string selectedFilteredItem = filteredList[currentFilteredItem];
        for (int i = 0; i < dataSize; i++)
        {
            if (selectedFilteredItem.compare(data[i]) == 0)
            {
                *currentItem = i;
                break;
            }
        }
    }

    return status;
}