#pragma once

#include "../bitfields/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

#pragma pack(push, 1)

// Trade Break Messages are sent when an execution on IEX is broken on that same trading day
struct TradeBreakMessage {

    SaleConditionFlags sale_condition_flags;
    Timestamp timestamp;
    Symbol symbol;
    Size size;
    Price price;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static TradeBreakMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeBreakMessage*>(buffer);
    }

    // parse method const
    static const TradeBreakMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeBreakMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeBreakMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeBreakMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
