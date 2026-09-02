#pragma once

#include "../bitfields/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

#pragma pack(push, 1)

// A non-displayed order on the book that executed against another non-displayed order on the book
struct TradeMessage {

    SaleConditionFlags sale_condition_flags;
    Timestamp timestamp;
    Symbol symbol;
    Size size;
    Price price;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
