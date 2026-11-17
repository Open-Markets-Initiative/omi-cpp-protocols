// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/SettlementValueMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PriceType.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// Index value messages contain the values associated with a calculated index. They are transmitted when an index is calculated.
struct SettlementValueMessage {

    ClassKey class_key;
    SecurityId security_id;
    PriceType price_type;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 23;

    // parse method
    static SettlementValueMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SettlementValueMessage*>(buffer);
    }

    // parse method const
    static const SettlementValueMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SettlementValueMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SettlementValueMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SettlementValueMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
