#include "rl_vamp.h"

BAKKESMOD_PLUGIN(rl_vamp, "rl-vamp", "1.0", PERMISSION_ALL)

bool bakkesmodLoaded = false;

void rl_vamp::onLoad() { // Function TAGame.ProductLoader_TA.HandleAssetLoaded
	bakkesmodLoaded = true;
}

void rl_vamp::onUnload() {
	//exit(0);
	delete GameHooks::hooksManager;
	std::cout << "[RLCHANGER::onUnload]: Destroying ImGui Kiero hook" << std::endl;
	kiero::shutdown();
	return;
}