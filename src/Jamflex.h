#include <Windows.h>
#include <stdint.h>

#define ATARAXIA

namespace Jamflex {
const static uintptr_t clientBase =
    reinterpret_cast<uintptr_t>(GetModuleHandleA("ataraxiaclient.exe"));

const static uintptr_t MouseHookLoc = 0xbc4cd8;
} // namespace Jamflex