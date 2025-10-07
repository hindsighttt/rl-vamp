#include "hooks.h"
#include "cars.h"

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
auto OriginalAddress = HOOKS::FindPattern(L"RocketLeague.exe", "? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? ? ? ? ? ? C3 ? ? ? ? ? ? ? ? ? E9"); // 0x41 0x8B 0x00

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

std::uint8_t* HOOKS::FindPattern(const wchar_t* wszModuleName, const char* szPattern)
{
    auto PatternToBytes = [](const char* pattern, std::vector<int>& bytes) {
        const char* current = pattern;
        while (*current) {
            if (*current == ' ') {
                ++current;
                continue;
            }
            if (*current == '?') {
                ++current;
                if (*current == '?') ++current;
                bytes.push_back(-1);
            } else {
                bytes.push_back(strtoul(current, const_cast<char**>(&current), 16));
            }
        }
    };

    HMODULE hModule = GetModuleHandleW(wszModuleName);
    if (!hModule) return nullptr;

    MODULEINFO modInfo = {};
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO)))
        return nullptr;

    std::uint8_t* start = reinterpret_cast<std::uint8_t*>(modInfo.lpBaseOfDll);
    std::size_t size = static_cast<std::size_t>(modInfo.SizeOfImage);

    std::vector<int> patternBytes;
    PatternToBytes(szPattern, patternBytes);
    std::size_t patternSize = patternBytes.size();

    for (std::size_t i = 0; i <= size - patternSize; ++i) {
        bool found = true;
        for (std::size_t j = 0; j < patternSize; ++j) {
            if (patternBytes[j] != -1 && start[i + j] != static_cast<std::uint8_t>(patternBytes[j])) {
                found = false;
                break;
            }
        }
        if (found) {
            return &start[i];
        }
    }
    return nullptr;
}

void HOOKS::SetupHooks()
{
	if (!steamDll)
		addr = epic_addr;
	else
		addr = steam_addr;
	if (OriginalAddress == nullptr)
		std::cerr << "[-] Pattern not found!" << std::endl;
	std::cout << "[+] MinHook Initialized" << std::endl;
	std::cout << "[+] Pattern found at: " << OriginalAddress << std::endl;
	MH_STATUS STATUS = MH_CreateHook(reinterpret_cast<void*>(OriginalAddress), &hkProcessObject, reinterpret_cast<void**>(&fnProcessObject));
	if (STATUS == MH_OK)
		std::cout << "[+] Hook Successfully Created" << std::endl;
	else
	{
		printf("[-] Failed To Create Hook\n");
		Sleep(200);
		exit(EXIT_FAILURE);
	}

	STATUS = MH_EnableHook(reinterpret_cast<void*>(OriginalAddress));
	if (STATUS == MH_OK)
		std::cout << "[+] Hook Successfully Enabled" << std::endl;
	else
	{
		std::cerr << "[-] Failed to enable hooks" << std::endl;
		Sleep(200);
		exit(EXIT_FAILURE);
	}
    HOOKS::init = true;
}