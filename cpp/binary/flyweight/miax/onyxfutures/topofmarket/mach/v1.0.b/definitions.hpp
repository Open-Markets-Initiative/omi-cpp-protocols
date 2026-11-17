// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: definitions.hpp
#pragma once

// Every flyweight view and reader of Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b.

#include "structs/MachPacketHeader.hpp"
#include "messages/SimpleInstrumentDefinitionMessage.hpp"
#include "groups/InstrumentLeg.hpp"
#include "messages/ComplexInstrumentDefinitionMessage.hpp"
#include "messages/SystemStateMessage.hpp"
#include "messages/InstrumentTradingStatusNotificationMessage.hpp"
#include "messages/BestBidAndOfferMessage.hpp"
#include "messages/LastSaleMessage.hpp"
#include "messages/TradeCancelMessage.hpp"
#include "messages/ApplicationMessage.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"

#include "PacketReader.hpp"
