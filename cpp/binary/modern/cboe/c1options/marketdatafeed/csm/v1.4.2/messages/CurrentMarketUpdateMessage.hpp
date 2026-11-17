// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/CurrentMarketUpdateMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/PriceType.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// The Current Market Update message contains real-time top of book market updates for a security.
struct CurrentMarketUpdateMessage {

    ClassKey class_key;
    SecurityId security_id;
    SecurityTradingStatus security_trading_status;
    PriceType price_type;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 12;

    // parse method
    static CurrentMarketUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CurrentMarketUpdateMessage*>(buffer);
    }

    // parse method const
    static const CurrentMarketUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CurrentMarketUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CurrentMarketUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CurrentMarketUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
