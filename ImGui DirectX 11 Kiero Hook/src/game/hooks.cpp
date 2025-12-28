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

uintptr_t base = (uintptr_t)GetModuleHandleA("RocketLeague.exe");
uintptr_t steamDll = (uintptr_t)GetModuleHandleA("steam_api64.dll");

// relative address will only be used as a fallback mechanism if the pattern changes
uintptr_t epic_addr = 0x3B42B0; // Epic
uintptr_t steam_addr = 0x3B2DF0; // Steam

uintptr_t addr;

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

typedef __int64(__fastcall* ProcessObject)(void* gameContext, void* unknown, void* gameObject);
ProcessObject fnProcessObject = nullptr;
ProcessObject fnProcessObjectOG;

__int64 __fastcall hkProcessObject(void* gameContext, void* unknown, void* gameObject) {
	if (HOOKS::enabled)
	{
		if (gameObject && IsValidCar((Car*)gameObject))
		{
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
	return fnProcessObject(gameContext, unknown, gameObject);
}

void HOOKS::SetupHooks()
{
	std::uint8_t* OriginalAddress = hooksManager->FindPattern(L"RocketLeague.exe", "? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? E9");
	if (!steamDll)
		addr = epic_addr;
	else
		addr = steam_addr;

	if (OriginalAddress == nullptr) {
		std::cerr << "[HOOKS::SetupHooks] Pattern not found!" << std::endl;
		return;
	}

	Hook& processObject = hooksManager->CreateHook(reinterpret_cast<void*>(OriginalAddress), &hkProcessObject, "ProcessObject");
	processObject.EnableHook();
	fnProcessObject = reinterpret_cast<ProcessObject>(processObject.GetStoredFunctionPtr());
	if (!fnProcessObject) {
		std::cerr << "[HOOKS::SetupHooks] Failed to obtain original function pointer" << std::endl;
		return;
	}

	HOOKS::init = true;
}