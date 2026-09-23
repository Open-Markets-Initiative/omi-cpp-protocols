#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/CanceledShares.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// This message is sent whenever an order on the book is modified as a result of a partial cancellation
struct OrderCancelMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    CanceledShares canceled_shares;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static OrderCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCancelMessage*>(buffer);
    }

    // parse method const
    static const OrderCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderCancelMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
