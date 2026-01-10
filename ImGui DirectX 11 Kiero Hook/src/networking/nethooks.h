#ifndef NETHOOKS_H
#define NETHOOKS_H

#include "../../lib/HookManager/HooksManager.hpp"

namespace NetHooks {
	extern HooksManager* hookManager;
	void SetupHooks();
}

#endif