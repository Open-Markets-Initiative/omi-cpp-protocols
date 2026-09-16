#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalOrderReferenceNumber.hpp"
#include "../types/NewOrderReferenceNumber.hpp"
#include "../types/Shares.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// This message is sent whenever an order on the book has been cancel-replaced
struct OrderReplaceMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    OriginalOrderReferenceNumber original_order_reference_number;
    NewOrderReferenceNumber new_order_reference_number;
    Shares shares;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'U';

    // parse method
    static OrderReplaceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderReplaceMessage*>(buffer);
    }

    // parse method const
    static const OrderReplaceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderReplaceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderReplaceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderReplaceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
