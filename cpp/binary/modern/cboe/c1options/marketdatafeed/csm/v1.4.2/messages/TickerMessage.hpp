// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/TickerMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PriceType.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// A Ticker message indicates that a trade or cancel has occurred.
struct TickerMessage {

    ClassKey class_key;
    SecurityId security_id;
    PriceType price_type;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 14;

    // parse method
    static TickerMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TickerMessage*>(buffer);
    }

    // parse method const
    static const TickerMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TickerMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TickerMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TickerMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
