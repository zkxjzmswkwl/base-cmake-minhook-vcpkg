#include <iostream>
#include <stdint.h>

#define uint unsigned int

// If you're working on a x86 client for whatever reason, __fastcall is not what you want.
#define Hook void __fastcall

using fn = uintptr_t *(*)(...);
fn oNodeAction;
fn oEntityAction;

struct ClientProt { // Best way to think of ClientProts is "Packet descriptor".
    uint32_t opcode;
    int32_t  packetSize;
};

struct MiniMenuPtr { // Every action in the game uses this structure to intake arguments.
    MiniMenuPtr(uint id, int x, int y) : id(id), x(x), y(y) {}
    MiniMenuPtr() {}

    char pad[0x58];
    uint id;
    int  x = 0;
    int  y = 0;
};

template <typename T> class SharedPtr { // Used constantly.
  public:
    uintptr_t *usuallyUseless;
    T         *ptr;
};

Hook NodeAction(void *sp, ClientProt *clientProt, SharedPtr<MiniMenuPtr> *miniMenu) {
    std::cout << clientProt->opcode << "\t" << clientProt->packetSize << "\n";
    std::cout << miniMenu->ptr->id << "," << miniMenu->ptr->x << "," << miniMenu->ptr->y << "\n";
    oNodeAction(sp, clientProt, miniMenu);
}

// Hook DoAction(void *a, uintptr_t *miniMenu, void *c) { uintptr_t ptr = *(uintptr_t *)(miniMenu + 0x8); }

Hook EntityAction(void *sp, ClientProt *clientProt, SharedPtr<MiniMenuPtr> *miniMenu) {
    std::cout << clientProt->opcode << "\t" << clientProt->packetSize << "\n";
    std::cout << miniMenu->ptr->id << "," << miniMenu->ptr->x << "," << miniMenu->ptr->y << "\n";
    oEntityAction(sp, clientProt, miniMenu);
}
