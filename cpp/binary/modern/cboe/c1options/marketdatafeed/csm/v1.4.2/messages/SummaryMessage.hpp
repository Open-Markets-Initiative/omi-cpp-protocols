// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/SummaryMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PriceType.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/OpenInterest.hpp"
#include "../structs/NetChgPrevDay.hpp"
#include "../structs/UnderlyingPx.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// Summary messages contain the end of session market data for each product.
struct SummaryMessage {

    ClassKey class_key;
    SecurityId security_id;
    PriceType price_type;
    TradeVolume trade_volume;
    OpenInterest open_interest;
    NetChgPrevDay net_chg_prev_day;
    UnderlyingPx underlying_px;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 24;

    // parse method
    static SummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SummaryMessage*>(buffer);
    }

    // parse method const
    static const SummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
