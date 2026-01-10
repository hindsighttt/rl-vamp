#include "RLCHANGER.h"

BAKKESMOD_PLUGIN(RLCHANGER, "RLCHANGER", "1.0", PERMISSION_ALL)

bool bakkesmodLoaded = false;

void RLCHANGER::onLoad() // Function TAGame.ProductLoader_TA.HandleAssetLoaded  
{
	bakkesmodLoaded = true;
}

void RLCHANGER::onUnload()
{
	//exit(0);
	delete GameHooks::hooksManager;
	std::cout << "[RLCHANGER::onUnload]: Destroying ImGui Kiero hook" << std::endl;
	kiero::shutdown();
	return;
}