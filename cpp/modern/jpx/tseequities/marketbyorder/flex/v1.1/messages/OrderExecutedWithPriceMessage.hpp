#pragma once

#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Volume.hpp"
#include "../types/MatchId.hpp"
#include "../types/ExecutionPrice.hpp"
#include "../types/AdoptedPricingMethod.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about registered orders in case of Itayose execution. Delivered when an execution occurs by the Itayose method or while an SQ or STQ is displayed.
struct OrderExecutedWithPriceMessage {

    TimeMicroseconds time_microseconds;
    OrderId order_id;
    Side side;
    Volume volume;
    MatchId match_id;
    ExecutionPrice execution_price;
    AdoptedPricingMethod adopted_pricing_method;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static OrderExecutedWithPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedWithPriceMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedWithPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedWithPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedWithPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedWithPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
