#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/NonDisplayedTradeTradeCond1.hpp"
#include "../types/Reserved3.hpp"
#include "../types/PriceType.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published as a result of a match between two non-displayed orders.
struct OptionsNonDisplayedTradeMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    TradeId trade_id;
    Price price;
    Volume volume;
    PrintableFlag printable_flag;
    NonDisplayedTradeTradeCond1 non_displayed_trade_trade_cond_1;
    Reserved3 reserved_3;
    PriceType price_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 310;

    // parse method
    static OptionsNonDisplayedTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsNonDisplayedTradeMessage*>(buffer);
    }

    // parse method const
    static const OptionsNonDisplayedTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsNonDisplayedTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsNonDisplayedTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsNonDisplayedTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
