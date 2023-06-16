#include "pch.h"

#include "Hooks/ServerReplicator.h"

static std::map<ServerReplicator*, RakPeerInterface*> rakPeers;

ServerReplicator__sendTop_t ServerReplicator__sendTop = (ServerReplicator__sendTop_t)ADDRESS_SERVERREPLICATOR__SENDTOP;
ServerReplicator__processTicket_t ServerReplicator__processTicket = (ServerReplicator__processTicket_t)ADDRESS_SERVERREPLICATOR__PROCESSTICKET;

void __fastcall ServerReplicator__sendTop_hook(ServerReplicator* _this, void*, RakPeerInterface* peer)
{
    if (_this->isAuthenticated)
    {
        ServerReplicator__sendTop(_this, peer);
    }
    else if (rakPeers.find(_this) == rakPeers.end())
    {
        rakPeers.insert(std::pair<ServerReplicator*, RakPeerInterface*>(_this, peer));
    }
}

void __fastcall ServerReplicator__processTicket_hook(ServerReplicator* _this, void*, Packet* packet)
{
    ServerReplicator__processTicket(_this, packet);

    auto pos = rakPeers.find(_this);
    if (_this->isAuthenticated)
    {
        ServerReplicator__sendTop_hook(_this, nullptr, pos->second);
    }
}