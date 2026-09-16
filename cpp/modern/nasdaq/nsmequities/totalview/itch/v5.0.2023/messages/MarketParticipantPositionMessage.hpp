#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Mpid.hpp"
#include "../types/Stock.hpp"
#include "../types/PrimaryMarketMaker.hpp"
#include "../types/MarketMakerMode.hpp"
#include "../types/MarketParticipantState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Nasdaq will send out this message only if Nasdaq Operations changes the status of a market participant firm in an issue
struct MarketParticipantPositionMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Mpid mpid;
    Stock stock;
    PrimaryMarketMaker primary_market_maker;
    MarketMakerMode market_maker_mode;
    MarketParticipantState market_participant_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static MarketParticipantPositionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketParticipantPositionMessage*>(buffer);
    }

    // parse method const
    static const MarketParticipantPositionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketParticipantPositionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketParticipantPositionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketParticipantPositionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
