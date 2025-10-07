#ifndef CARS_H
# define CARS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

struct Item
{
	unsigned int ingameID;
	std::string type;
	std::string ingameName;
};

namespace CARS
{
	extern std::vector<Item> CarsList;
	extern std::vector<Item> ItemList;
	extern std::vector<Item> WheelsList;
	extern std::vector<Item> BoostsList;
	extern std::vector<Item> AntennasList;
	extern std::vector<Item> ToppersList;
	extern std::vector<Item> GoalsList;

	extern std::vector<int> ValidCars;
	extern std::vector<int> ValidWheels;
	void LoadAllItems(std::string file_path);
}

#endif CARS_H