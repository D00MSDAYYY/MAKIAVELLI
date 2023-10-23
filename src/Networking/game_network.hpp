#pragma once

#include "3rdParty/net_common.hpp"
#include "3rdParty/net_client.hpp"
#include "3rdParty/net_server.hpp"
enum class MSG_FROM : uint32_t
{
	SERVER_NEXT_TURN,
	SERVER_HANDSHAKE,

	SERVER_REQUEST_EXCHANGE_RES,
	
	SERVER_DATA_COUNTRY, //! can be used to prove that activity was valid and activity points can be decreased

	// CLIENT_NEXT_TURN,

	CLIENT_REQUEST_EXCHANGE_RES,
	CLIENT_ACCEPT_EXCHANGE_RES,

	CLIENT_BUY_POINTS,
	CLIENT_BUY_LOCATIONS
};
