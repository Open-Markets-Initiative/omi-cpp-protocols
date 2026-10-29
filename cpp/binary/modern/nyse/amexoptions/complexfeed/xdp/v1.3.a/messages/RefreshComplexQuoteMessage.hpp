#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/AskPrice.hpp"
#include "../types/BidPrice.hpp"
#include "../types/AskVolume.hpp"
#include "../types/BidVolume.hpp"
#include "../types/AskCustomerVolume.hpp"
#include "../types/BidCustomerVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Refresh Complex Quote message is sent in the event no quote messages are published for the symbol for 2 consecutive minutes.
struct RefreshComplexQuoteMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    ComplexIndex complex_index;
    SymbolSeqNum symbol_seq_num;
    AskPrice ask_price;
    BidPrice bid_price;
    AskVolume ask_volume;
    BidVolume bid_volume;
    AskCustomerVolume ask_customer_volume;
    BidCustomerVolume bid_customer_volume;
    QuoteCondition quote_condition;
    Reserved1 reserved_1;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 511;

    // parse method
    static RefreshComplexQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshComplexQuoteMessage*>(buffer);
    }

    // parse method const
    static const RefreshComplexQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshComplexQuoteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshComplexQuoteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RefreshComplexQuoteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
