#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskVolume.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/AskCustomerVolume.hpp"
#include "../types/BidCustomerVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// An Options quote message is sent when any event results in a new top of book value on either side of the market
struct OptionsQuoteMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    AskPrice ask_price;
    AskVolume ask_volume;
    BidPrice bid_price;
    BidVolume bid_volume;
    QuoteCondition quote_condition;
    Reserved1 reserved_1;
    AskCustomerVolume ask_customer_volume;
    BidCustomerVolume bid_customer_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 340;

    // parse method
    static OptionsQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsQuoteMessage*>(buffer);
    }

    // parse method const
    static const OptionsQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsQuoteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsQuoteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsQuoteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
