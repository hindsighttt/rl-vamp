#ifndef HOOKSMANAGER_HPP
# define HOOKSMANAGER_HPP

#define PATH_TO_MINHOOK "../kiero/minhook/include/Minhook.h"

#include PATH_TO_MINHOOK
#include <Psapi.h>
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

class Hook
{
public:
    Hook(std::string functionName);
    Hook();
    ~Hook();
public:
    bool        InitializeHook(LPVOID targetFunctionAddr, LPVOID detourFunctionPtr);
    void        EnableHook();
    void        DisableHook();
    bool        ToggleHook();
    LPVOID      GetStoredFunctionPtr();
    std::string GetFunctionName();
private:
    std::string _functionName;
    bool        _state;
    LPVOID      _functionAddr;
    LPVOID      _detourFunctionPtr;
    LPVOID      _storedFunctionPtr;
};

class HooksManager
{
public:
    HooksManager();
    ~HooksManager();
public:
    std::uint8_t*   FindPattern(const wchar_t* wszModuleName, const char *szPattern);
    Hook            &CreateHook(LPVOID targetFunctionAddr, LPVOID detourFunctionPtr, std::string functionName);
    Hook            *GetHookByName(std::string functionName);
    void            DestroyHook(std::string functionName); // NOT_IMPLEMENTED
    void            DestroyHook(Hook *hook); // NOT_IMPLEMENTED
    bool            EnableAllHooks();
    bool            DisableAllHooks();
    void            DestroyAllHooks();
private:
    std::vector<Hook*> _hookVector;
};

#endif // !HOOKSMANAGER_HPP