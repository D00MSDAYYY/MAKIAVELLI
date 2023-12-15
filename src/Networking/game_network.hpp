#pragma once

#include "3rdParty/net_client.hpp"
#include "3rdParty/net_common.hpp"
#include "3rdParty/net_server.hpp"

enum class MSG_FROM : uint32_t
{
    SERVER_HANDSHAKE,

    SERVER_DATA_COUNTRY,

    SERVER_REQUEST_EXCHANGE_RES,

    SERVER_NEW_CARD,      // TODO! update server's OnMessage

    SERVER_TEXT_MESSAGE,  // TODO! update server's OnMessage

    // CLIENT_NEXT_TURN,

    CLIENT_REQUEST_EXCHANGE_RES,
    CLIENT_ACCEPT_EXCHANGE_RES,

    CLIENT_BUY_POINTS,
    CLIENT_BUY_LOCATIONS,

    CLIENT_TEXT_MESSAGE
};
