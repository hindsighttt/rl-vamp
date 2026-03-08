#include "hooks.h"

namespace GameHooks {
	HooksManager* hooksManager = new HooksManager;
	bool enabled = false;
	bool g_init = false;
	int carID = 0;
	int wheelID = 0;
	int boostID = 0;
	int hatID = 0;
	int decalID = 0;
	int antennaID = 0;
	int goalExplosionID = 0;
	int lastLoadedCarID = 0;
}

bool IsValidCar(Car* car) 
{
	if (!car) 
		return false;
	if (std::find(CARS::ValidCars.begin(), CARS::ValidCars.end(), car->carID) != CARS::ValidCars.end() &&
		std::find(CARS::ValidWheels.begin(), CARS::ValidWheels.end(), car->wheelID) != CARS::ValidWheels.end()) 
		return true;
	return false;
}

__int64 __fastcall hkProcessObject(void* caller, void* unknown, void* gameObject) {
	static GameHooks::ProcessObject originalFunction = reinterpret_cast<GameHooks::ProcessObject>(GameHooks::hooksManager->GetHookByName("ProcessObject")->GetStoredFunctionPtr());

	if (GameHooks::enabled) {
		if (gameObject && IsValidCar((Car*)gameObject)) {
			GameHooks::lastLoadedCarID = ((Car*)gameObject)->carID;
			Car* car = (Car*)gameObject;
			if (GameHooks::carID != 0)
				car->carID = GameHooks::carID;
			if (GameHooks::wheelID != 0)
				car->wheelID = GameHooks::wheelID;
			if (GameHooks::boostID != 0)
				car->boostID = GameHooks::boostID;
			if (GameHooks::hatID != 0)
				car->topperID = GameHooks::hatID;
			if (GameHooks::decalID != 0)
				car->decalID = GameHooks::decalID;
			if (GameHooks::antennaID != 0)
				car->antennaID = GameHooks::antennaID;
			if (GameHooks::goalExplosionID != 0)
				car->goalExplosionID = GameHooks::goalExplosionID;
		}
	}
	return originalFunction(caller, unknown, gameObject);
}

__int64 __fastcall hkProcessObjectPreview(void* caller, void* unknown, __int64 gameObject) { // only used to dump the carID from the shop
	static GameHooks::ProcessObjectPreview originalFunction = reinterpret_cast<GameHooks::ProcessObjectPreview>(GameHooks::hooksManager->GetHookByName("ProcessObjectPreview")->GetStoredFunctionPtr());

	Car* car = *(Car**)gameObject;
	GameHooks::lastLoadedCarID = car->carID;
	return originalFunction(caller, unknown, gameObject);
}

void GameHooks::SetupHooks()
{
	std::uint8_t* processObjectAddress = hooksManager->FindPattern(L"RocketLeague.exe", "? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? E9");
	if (processObjectAddress == nullptr) {
		std::cerr << "[GameHooks::SetupHooks] Pattern not found!" << std::endl;
		return;
	}
	Hook& processObject = hooksManager->CreateHook(reinterpret_cast<void*>(processObjectAddress), &hkProcessObject, "ProcessObject");
	processObject.EnableHook();

	std::uint8_t* processObjectPreviewAddress = hooksManager->FindPattern(L"RocketLeague.exe", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 49 8B F0 4C 8B F9");
	if (processObjectAddress == nullptr) {
		std::cerr << "[GameHooks::SetupHooks] Pattern not found!" << std::endl;
		return;
	}
	Hook& processObjectPreview = hooksManager->CreateHook(reinterpret_cast<void*>(processObjectPreviewAddress), &hkProcessObjectPreview, "ProcessObjectPreview");
	#ifdef _DEBUG
	processObjectPreview.EnableHook();
	#endif

	GameHooks::g_init = true;
}