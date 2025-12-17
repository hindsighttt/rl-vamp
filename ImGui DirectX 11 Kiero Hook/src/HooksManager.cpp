#include "HooksManager.hpp"

Hook::Hook(std::string functionName)
{
    this->_functionName = functionName;
    this->_state = false;
    this->_functionAddr = nullptr;
    this->_detourFunctionPtr = nullptr;
    this->_storedFunctionPtr = nullptr;
}

Hook::Hook()
{
    this->_detourFunctionPtr = nullptr;
    this->_functionAddr = nullptr;
    this->_storedFunctionPtr = nullptr;
    this->_state = false;
}

Hook::~Hook() // Disables the hook and removes it
{
    if (this->_functionAddr)
        this->DisableHook();
    if (this->_functionAddr)
        MH_RemoveHook(this->_functionAddr);
    std::cout << "[Hook::~Hook]: Successfully destroyed hook " << this->_functionName << std::endl;
}

bool Hook::InitializeHook(LPVOID targetFunctionAddr, LPVOID detourFunctionPtr)
{
    MH_STATUS currentStatus = MH_CreateHook(targetFunctionAddr, detourFunctionPtr, &this->_storedFunctionPtr);
    if (currentStatus != MH_OK)
        return false;
    this->_detourFunctionPtr = detourFunctionPtr;
    this->_functionAddr = targetFunctionAddr;
    return true;
}

void Hook::EnableHook()
{
    if (!this->_functionAddr) return;
    MH_STATUS currentStatus = MH_EnableHook(this->_functionAddr);
    if (currentStatus != MH_OK)
        return;
    this->_state = true;
}

void Hook::DisableHook()
{
    if (!this->_functionAddr) return;
    MH_STATUS currentStatus = MH_DisableHook(this->_functionAddr);
    if (currentStatus != MH_OK)
        return;
    this->_state = false;
}

bool Hook::ToggleHook()
{
    if (this->_state)
        this->DisableHook();
    else
        this->EnableHook();
    return this->_state;
}

LPVOID Hook::GetStoredFunctionPtr()
{
    return this->_storedFunctionPtr;
}

std::string Hook::GetFunctionName()
{
    return this->_functionName;
}

HooksManager::HooksManager()
{
    MH_STATUS currentStatus = MH_Initialize();
    if (currentStatus != MH_OK && currentStatus != MH_ERROR_ALREADY_INITIALIZED)
        std::cerr << "[HooksManager::HooksManager]: Failed to initialize MinHook" << std::endl;
}

HooksManager::~HooksManager()
{
    this->DestroyAllHooks();
}

std::uint8_t *HooksManager::FindPattern(const wchar_t *wszModuleName, const char *szPattern)
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

Hook &HooksManager::CreateHook(LPVOID targetFunctionAddr, LPVOID detourFunctionPtr, std::string functionName)
{
    Hook* hook = new Hook(functionName);
    bool success = hook->InitializeHook(targetFunctionAddr, detourFunctionPtr);
    if (!success)
    {
        std::cerr << "[HooksManager::CreateHook]: Failed to initialized hook for " << functionName << std::endl;
        return *hook;
    }
    this->_hookVector.push_back(hook);
    std::cout << "[HooksManager::CreateHook]: Successfully hooked " << functionName << std::endl;
    return (*hook);
}

Hook HooksManager::GetHookByName(std::string functionName)
{
    for (int i = 0; i < this->_hookVector.size(); i++)
    {
        int diff = this->_hookVector[i]->GetFunctionName().compare(functionName);
        if (diff == 0)
            return *this->_hookVector[i];
    }
    return Hook();
}

bool HooksManager::EnableAllHooks() // we could use MH_EnableHook(MH_ALL_HOOKS) but it would throw off our tracked enabled state
{
    for (int i = 0; i < this->_hookVector.size(); i++)
        this->_hookVector[i]->EnableHook(); // this ensures we retain the state of each hook even if some fail to enable
    return true;
}

bool HooksManager::DisableAllHooks()
{
    for (int i = 0; i < this->_hookVector.size(); i++)
        this->_hookVector[i]->DisableHook();
    return true;
}

void HooksManager::DestroyAllHooks()
{
    if (this->_hookVector.size() > 0)
    {
        for (int i = 0; i < this->_hookVector.size(); i++)
        {
            delete this->_hookVector[i];
            this->_hookVector.pop_back();
        }
    }
}
