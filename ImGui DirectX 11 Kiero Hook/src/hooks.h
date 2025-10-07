#pragma once
#include "../kiero/minhook/include/Minhook.h"
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <Psapi.h>
#include <algorithm>

namespace HOOKS
{
	extern bool init;
    extern bool enabled;
    extern int carID;
    extern int wheelID;
    extern int boostID;
    extern int hatID;
    extern int decalID;
    extern int antennaID;
    extern int goalExplosionID;
    std::uint8_t* FindPattern(const wchar_t* wszModuleName, const char* szPattern);
    void SetupHooks();
}

class Car
{
public:
    uint32_t carID; //0x0000
    uint32_t decalID; //0x0004
    uint32_t wheelID; //0x0008
    uint32_t boostID; //0x000C
    uint32_t antennaID; //0x0010
    uint32_t topperID; //0x0014
    uint32_t N0000000E[5]; //0x0018
    uint32_t lastID; //0x002C
    uint32_t N00000012; //0x0030
    uint32_t engineAudioID; //0x0034
    uint32_t trailID; //0x0038
    uint32_t goalExplosionID; //0x003C
    // uint32_t playerBannerID; // 0x0040
    // uint32_t playerAvatarBorderID; // 0x0050
}; //Size: 0x0438