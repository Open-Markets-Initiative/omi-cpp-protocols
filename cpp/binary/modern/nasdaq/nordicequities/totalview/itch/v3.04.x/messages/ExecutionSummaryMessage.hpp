#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderBook.hpp"
#include "../types/AggressingSide.hpp"
#include "../types/Quantity.hpp"
#include "../types/HiddenQuantity.hpp"
#include "../types/StpCancelQuantity.hpp"
#include "../types/FarPrice.hpp"
#include "../types/AddQuantity.hpp"
#include "../types/NumberOfLitExecutions.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// Summary information disseminated before the individual trades
struct ExecutionSummaryMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderBook order_book;
    AggressingSide aggressing_side;
    Quantity quantity;
    HiddenQuantity hidden_quantity;
    StpCancelQuantity stp_cancel_quantity;
    FarPrice far_price;
    AddQuantity add_quantity;
    NumberOfLitExecutions number_of_lit_executions;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'K';

    // parse method
    static ExecutionSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionSummaryMessage*>(buffer);
    }

    // parse method const
    static const ExecutionSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ExecutionSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ExecutionSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
