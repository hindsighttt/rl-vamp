#include "RLCHANGER.h"
#include <iostream>
#include <Windows.h>

BAKKESMOD_PLUGIN(RLCHANGER, "RLCHANGER", "1.0", PERMISSION_ALL)

void RLCHANGER::onLoad()
{
	FILE* placeholder;
	AllocConsole();
	freopen_s(&placeholder, "CONOUT$", "w", stdout);
	std::cout << "[+] Running in " << std::filesystem::current_path() << std::endl;
	std::cout << "[+] Process ID: " << GetCurrentProcessId() << std::endl << std::endl;
}

void RLCHANGER::onUnload()
{

}