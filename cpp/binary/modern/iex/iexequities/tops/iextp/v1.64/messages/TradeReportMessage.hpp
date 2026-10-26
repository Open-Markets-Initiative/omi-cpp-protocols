#pragma once

#include "../bitfields/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

#pragma pack(push, 1)

// Trade Report Messages are sent when an order on the IEX Order Book is executed in whole or in part
struct TradeReportMessage {

    SaleConditionFlags sale_condition_flags;
    Timestamp timestamp;
    Symbol symbol;
    Size size;
    Price price;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static TradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReportMessage*>(buffer);
    }

    // parse method const
    static const TradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReportMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeReportMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeReportMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
