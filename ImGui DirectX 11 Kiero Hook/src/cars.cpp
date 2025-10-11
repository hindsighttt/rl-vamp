#include "cars.h"

std::vector<Item> CARS::CarsList;
std::vector<Item> CARS::WheelsList;
std::vector<Item> CARS::BoostsList;
std::vector<Item> CARS::AntennasList;
std::vector<Item> CARS::ToppersList;
std::vector<Item> CARS::GoalsList;
std::vector<Item> CARS::ItemList;
std::vector<int> CARS::ValidCars;
std::vector<int> CARS::ValidWheels;

void CARS::LoadAllItems(std::string file_path)  
{  
   std::ifstream file(file_path);  
   if (!file.is_open())   
   {  
       std::cerr << "[-] Failed to open file: " << file_path << std::endl;  
       return;  
   }  

   Item NoneItem;
   NoneItem.ingameID = 0;
   NoneItem.ingameName = "None";
   CarsList.push_back(NoneItem);
   WheelsList.push_back(NoneItem);
   BoostsList.push_back(NoneItem);
   AntennasList.push_back(NoneItem);
   ToppersList.push_back(NoneItem);
   GoalsList.push_back(NoneItem);
 
   std::vector<std::pair<std::string, int>> cars;  
   std::string line;  
   while (std::getline(file, line)) {  
       std::istringstream ss(line);  
       std::string id_str, type, fullname, name;  
       std::getline(ss, id_str, ',');  
       std::getline(ss, type, ',');  
       std::getline(ss, fullname, ',');  
       std::getline(ss, name, ',');  
 
       Item current_item;  
       current_item.ingameID = std::atoi(id_str.c_str());  
       current_item.type = type;  
       current_item.ingameName = name;  
 
	   if (type == "Body")
	   {
		   Item current_item;
		   current_item.ingameID = std::atoi(id_str.c_str());
		   current_item.type = type;
		   current_item.ingameName = name;

		   CARS::CarsList.push_back(current_item);
		   CARS::ValidCars.push_back(std::atoi(id_str.c_str()));
	   }
	   else if (type == "Wheels")
	   {
		   Item current_item;
		   current_item.ingameID = std::atoi(id_str.c_str());
		   current_item.type = type;
		   current_item.ingameName = name;

		   CARS::WheelsList.push_back(current_item);
		   CARS::ValidWheels.push_back(std::atoi(id_str.c_str()));
	   }
	   else if (type == "Boost")
	   {
		   Item current_item;
		   current_item.ingameID = std::atoi(id_str.c_str());
		   current_item.type = type;
		   current_item.ingameName = name;

		   CARS::BoostsList.push_back(current_item);
	   }
	   else if (type == "Antenna")
	   {
		   Item current_item;
		   current_item.ingameID = std::atoi(id_str.c_str());
		   current_item.type = type;
		   current_item.ingameName = name;

		   CARS::AntennasList.push_back(current_item);
	   }
	   else if (type == "Hat")
	   {
		   Item current_item;
		   current_item.ingameID = std::atoi(id_str.c_str());
		   current_item.type = type;
		   current_item.ingameName = name;

		   CARS::ToppersList.push_back(current_item);
	   }
	   std::cout << "[+] Loaded " << current_item.ingameName << ": " << current_item.ingameID << std::endl;
   }  
   file.close();
   std::cout << "[+] Loaded " << CARS::CarsList.size()
	   + CARS::WheelsList.size()
	   + CARS::BoostsList.size()
	   + CARS::AntennasList.size()
	   + CARS::ToppersList.size()
	   << " items" << std::endl;
}