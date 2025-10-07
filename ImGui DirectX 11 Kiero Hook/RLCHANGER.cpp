#include "RLCHANGER.h"
#include <iostream>
#include <Windows.h>

BAKKESMOD_PLUGIN(RLCHANGER, "RLCHANGER", "1.0", PERMISSION_ALL)

void RLCHANGER::onLoad()
{

}

void RLCHANGER::onUnload()
{
	exit(0);
}