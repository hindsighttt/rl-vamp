#include "RLCHANGER.h"

BAKKESMOD_PLUGIN(RLCHANGER, "RLCHANGER", "1.0", PERMISSION_ALL)

void RLCHANGER::onLoad() // Function TAGame.ProductLoader_TA.HandleAssetLoaded  
{

}

void RLCHANGER::onUnload()
{
	//exit(0);
	delete HOOKS::hooksManager;
	std::cout << "[RLCHANGER::onUnload]: Destroying ImGui Kiero hook" << std::endl;
	kiero::shutdown();
	return;
}