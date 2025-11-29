#include "../include/filtered_combo.hpp"

bool ImGui::FilteredCombo(const char *label, int *currentItem, std::vector<std::string> data,  int itemsCount, const char *filter)
{
    std::vector<const char *> filteredList;
    int dataSize = data.size();
    if (filter != nullptr && strlen(filter) > 0)
    {
        for (int i = 0; i < dataSize; i++)
        {
			std::string currentEntry = data[i];
			std::string filterLower = filter;
			std::transform(currentEntry.begin(), currentEntry.end(), currentEntry.begin(), ::tolower);	
			std::transform(filterLower.begin(), filterLower.end(), filterLower.begin(), ::tolower);	
            int position = currentEntry.find(filterLower);
            if (position == std::string::npos)
                continue;
            filteredList.push_back(data[i].c_str());
        }
    }
    else
    {
        for (int i = 0; i < dataSize; i++)
            filteredList.push_back(data[i].c_str());
    }
	int currentFilteredItem = 0;
	if (strlen(filter) <= 0)
		currentFilteredItem = *currentItem;
	int filteredCount = static_cast<int>(filteredList.size());
	bool status = ImGui::Combo(label, &currentFilteredItem, filteredList.data(), filteredCount);
	if (status)
	{
		std::string selectedFilteredItem = filteredList[currentFilteredItem];	
		for (int i = 0; i < dataSize ;i++)
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