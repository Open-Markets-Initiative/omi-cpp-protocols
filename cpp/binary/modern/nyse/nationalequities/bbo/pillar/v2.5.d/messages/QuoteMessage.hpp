#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskVolume.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/RpiIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

#pragma pack(push, 1)

// A quote message is sent when any event results in a new top of book value on either side of the market.
struct QuoteMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    AskPrice ask_price;
    AskVolume ask_volume;
    BidPrice bid_price;
    BidVolume bid_volume;
    QuoteCondition quote_condition;
    RpiIndicator rpi_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 140;

    // parse method
    static QuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteMessage*>(buffer);
    }

    // parse method const
    static const QuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
