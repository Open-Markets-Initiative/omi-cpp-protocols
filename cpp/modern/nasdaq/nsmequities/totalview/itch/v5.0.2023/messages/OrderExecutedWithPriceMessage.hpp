#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/ExecutedShares.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Printable.hpp"
#include "../types/ExecutionPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// This message is sent whenever an order on the book is executed in whole or in part at a price different from the initial display price
struct OrderExecutedWithPriceMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    ExecutedShares executed_shares;
    MatchNumber match_number;
    Printable printable;
    ExecutionPrice execution_price;

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
