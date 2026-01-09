#pragma once
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "lib/kiero/kiero.h"
#include "lib/imgui/imgui.h"
#include "lib/imgui/imgui_impl_win32.h"
#include "lib/imgui/imgui_impl_dx11.h"
#include "src/game/hooks.h"
#include "src/game/cars.h"
#include "src/gui/GUI.h"
#include "src/misc/preset.h"
#include "RLCHANGER.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;