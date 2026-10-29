#pragma once

// Every flyweight view and reader of Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a.

#include "structs/SendTime.hpp"
#include "structs/PacketHeader.hpp"
#include "structs/MessageHeader.hpp"
#include "messages/ComplexQuoteMessage.hpp"
#include "messages/ComplexTradeMessage.hpp"
#include "messages/ComplexCrossingRfqMessage.hpp"
#include "messages/ComplexCubeRfqMessage.hpp"
#include "messages/ComplexStatusMessage.hpp"
#include "messages/RefreshComplexQuoteMessage.hpp"
#include "messages/RefreshComplexTradeMessage.hpp"
#include "groups/LegDefinition.hpp"
#include "messages/ComplexSymbolDefinitionMessage.hpp"
#include "messages/StreamIdMessage.hpp"
#include "messages/SequenceNumberResetMessage.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"

#include "PacketReader.hpp"
