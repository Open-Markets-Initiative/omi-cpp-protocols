// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/CurrentMarketRefreshMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/PriceType.hpp"
#include "../types/ApplSeqNum.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// The Current Market Refresh message contains a snapshot of the current market information for one security along with the quantities and volume types for that particular security.
struct CurrentMarketRefreshMessage {

    ClassKey class_key;
    SecurityId security_id;
    SecurityTradingStatus security_trading_status;
    PriceType price_type;
    ApplSeqNum appl_seq_num;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 11;

    // parse method
    static CurrentMarketRefreshMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CurrentMarketRefreshMessage*>(buffer);
    }

    // parse method const
    static const CurrentMarketRefreshMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CurrentMarketRefreshMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CurrentMarketRefreshMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CurrentMarketRefreshMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
