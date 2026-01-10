#include "hooks.h"

HooksManager *HOOKS::hooksManager = new HooksManager;
bool HOOKS::enabled = false;
bool HOOKS::init = false;
int HOOKS::carID = 0;
int HOOKS::wheelID = 0;
int HOOKS::boostID = 0;
int HOOKS::hatID = 0;
int HOOKS::decalID = 0;
int HOOKS::antennaID = 0;
int HOOKS::goalExplosionID = 0;
int HOOKS::lastLoadedCarID = 0;

bool IsValidCar(Car* car) 
{
	if (!car) 
		return false;
	if (std::find(CARS::ValidCars.begin(), CARS::ValidCars.end(), car->carID) != CARS::ValidCars.end() &&
		std::find(CARS::ValidWheels.begin(), CARS::ValidWheels.end(), car->wheelID) != CARS::ValidWheels.end()) 
	{
		return true;
	}
	return false;
}

typedef __int64(__fastcall* ProcessObject)(void* caller, void* unknown, void* gameObject);
ProcessObject fnProcessObject = nullptr;

__int64 __fastcall hkProcessObject(void* caller, void* unknown, void* gameObject) {

	if (HOOKS::enabled) {
		if (gameObject && IsValidCar((Car*)gameObject)) {
			HOOKS::lastLoadedCarID = ((Car*)gameObject)->carID;
			Car* car = (Car*)gameObject;
			if (HOOKS::carID != 0)
				car->carID = HOOKS::carID;
			if (HOOKS::wheelID != 0)
				car->wheelID = HOOKS::wheelID;
			if (HOOKS::boostID != 0)
				car->boostID = HOOKS::boostID;
			if (HOOKS::hatID != 0)
				car->topperID = HOOKS::hatID;
			if (HOOKS::decalID != 0)
				car->decalID = HOOKS::decalID;
			if (HOOKS::antennaID != 0)
				car->antennaID = HOOKS::antennaID;
			if (HOOKS::goalExplosionID != 0)
				car->goalExplosionID = HOOKS::goalExplosionID;
		}
	}

	return fnProcessObject(caller, unknown, gameObject);
}

typedef __int64(__fastcall* ProcessObjectPreview)(void * caller, void *a2, __int64 a3);
ProcessObjectPreview fnProcessObjectPreview = nullptr;
ProcessObjectPreview fnProcessObjectPreviewOG;
__int64 __fastcall hkProcessObjectPreview(void *caller, void *a2, __int64 a3) { // only used to dump the carID from the shop
	Car* car = *(Car**)a3;
	HOOKS::lastLoadedCarID = car->carID;
	return fnProcessObjectPreview(caller, a2, a3);
}

void HOOKS::SetupHooks()
{
	std::uint8_t* processObjectAddress = hooksManager->FindPattern(L"RocketLeague.exe", "? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? E9");
	if (processObjectAddress == nullptr) {
		std::cerr << "[HOOKS::SetupHooks] Pattern not found!" << std::endl;
		return;
	}
	Hook& processObject = hooksManager->CreateHook(reinterpret_cast<void*>(processObjectAddress), &hkProcessObject, "ProcessObject");
	processObject.EnableHook();
	fnProcessObject = reinterpret_cast<ProcessObject>(processObject.GetStoredFunctionPtr());
	if (!fnProcessObject) {
		std::cerr << "[HOOKS::SetupHooks] Failed to obtain original function pointer" << std::endl;
		return;
	}

	std::uint8_t* processObjectPreviewAddress = hooksManager->FindPattern(L"RocketLeague.exe", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 49 8B F0 4C 8B F9");
	if (processObjectAddress == nullptr) {
		std::cerr << "[HOOKS::SetupHooks] Pattern not found!" << std::endl;
		return;
	}
	Hook& processObjectPreview = hooksManager->CreateHook(reinterpret_cast<void*>(processObjectPreviewAddress), &hkProcessObjectPreview, "ProcessObjectPreview");
	processObjectPreview.EnableHook();
	fnProcessObjectPreview = reinterpret_cast<ProcessObjectPreview>(processObjectPreview.GetStoredFunctionPtr());
	if (!fnProcessObjectPreview) {
		std::cerr << "[HOOKS::SetupHooks] Failed to obtain original function pointer" << std::endl;
		return;
	}

	#ifndef _DEBUG
	processObjectPreview.DisableHook();
	#endif

	HOOKS::init = true;
}