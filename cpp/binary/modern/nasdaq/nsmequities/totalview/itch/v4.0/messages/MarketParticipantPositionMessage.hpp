#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/Mpid.hpp"
#include "../types/Stock.hpp"
#include "../types/PrimaryMarketMaker.hpp"
#include "../types/MarketMakerMode.hpp"
#include "../types/MarketParticipantState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// At the start of each trading day, NASDAQ disseminates a spin of market participant position messages. Throughout the day, NASDAQ will send out this message only if NASDAQ Operations changes the status of a market participant firm in an issue.
struct MarketParticipantPositionMessage {

    Nanoseconds nanoseconds;
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
