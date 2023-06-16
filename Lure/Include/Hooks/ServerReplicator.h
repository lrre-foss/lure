#pragma once

#include "Configuration.h"

struct Packet
{
    void* padding1[7];
    unsigned int length;
    void* padding2[1];
    unsigned char* data;
};

struct ConcurrentRakPeer {};
struct RakPeerInterface {};

struct ServerReplicator
{
    void* padding1[1869]; // offset of 0 -> 7476
    bool padding2;        // offset of 7476 -> 7477
    bool isAuthenticated; // offset of 7477 -> 7478
};

typedef void(__thiscall* ServerReplicator__sendTop_t)(ServerReplicator* _this, RakPeerInterface* peer);
typedef void(__thiscall* ServerReplicator__processTicket_t)(ServerReplicator* _this, Packet* packet);

void __fastcall ServerReplicator__sendTop_hook(ServerReplicator* _this, void*, RakPeerInterface* peer);
void __fastcall ServerReplicator__processTicket_hook(ServerReplicator* _this, void*, Packet* packet);

extern ServerReplicator__sendTop_t ServerReplicator__sendTop;
extern ServerReplicator__processTicket_t ServerReplicator__processTicket;