#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <iostream>
#include <Windows.h>
#include "lib/kiero/kiero.h"
#include "src/game/hooks.h"

#pragma comment( lib, "pluginsdk.lib")

extern bool bakkesmodLoaded;

class rl_vamp : public BakkesMod::Plugin::BakkesModPlugin
{
public:
	void onLoad() override;
	void onUnload() override;
};

