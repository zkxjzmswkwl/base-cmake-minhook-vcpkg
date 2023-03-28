#include <iostream>
#include <stdint.h>

#define uint unsigned int

#define Hook void __fastcall

using fn = uintptr_t *(*)(...);
fn oNodeAction;
fn oEntityAction;

struct ClientProt {
    uint32_t opcode;
    int32_t packetSize;
};

class MiniMenuPtr {
  public:
    char pad[0x58];
    uint identifier;
    int x = 0;
    int y = 0;
};

class SharedPtr {
  public:
    uintptr_t *usuallyUseless;
    MiniMenuPtr *ptr;
};

Hook NodeAction(void *sp, ClientProt *clientProt, SharedPtr *miniMenu) {
    std::cout << clientProt->opcode << "\t" << clientProt->packetSize << "\n";
    std::cout << miniMenu->ptr->identifier << "," << miniMenu->ptr->x << ","
              << miniMenu->ptr->y << "\n";
    oNodeAction(sp, clientProt, miniMenu);
}

Hook DoAction(void *a, uintptr_t *miniMenu, void *c) {
    uintptr_t ptr = *(uintptr_t *)(miniMenu + 0x8);
}

Hook EntityAction(void *sp, ClientProt *clientProt, SharedPtr *miniMenu) {
    std::cout << clientProt->opcode << "\t" << clientProt->packetSize << "\n";
    std::cout << miniMenu->ptr->identifier << "," << miniMenu->ptr->x << ","
              << miniMenu->ptr->y << "\n";
    oNodeAction(sp, clientProt, miniMenu);
}
