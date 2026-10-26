#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
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

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Execution Summary Message
struct execution_summary_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_book order_book;
        itch_totalview::aggressing_side aggressing_side;
        itch_totalview::quantity quantity;
        itch_totalview::hidden_quantity hidden_quantity;
        itch_totalview::stp_cancel_quantity stp_cancel_quantity;
        itch_totalview::far_price far_price;
        itch_totalview::add_quantity add_quantity;
        itch_totalview::number_of_lit_executions number_of_lit_executions;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::execution_summary_message};

    fields_type fields;

    // parse method
    static execution_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_summary_message*>(buffer);
    }

    // parse method const
    static const execution_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_summary_message::fields_type, timestamp) == 0, "unexpected offset of execution_summary_message::fields_type::timestamp");
static_assert(offsetof(execution_summary_message::fields_type, tracking_number) == 8, "unexpected offset of execution_summary_message::fields_type::tracking_number");
static_assert(offsetof(execution_summary_message::fields_type, order_book) == 10, "unexpected offset of execution_summary_message::fields_type::order_book");
static_assert(offsetof(execution_summary_message::fields_type, aggressing_side) == 14, "unexpected offset of execution_summary_message::fields_type::aggressing_side");
static_assert(offsetof(execution_summary_message::fields_type, quantity) == 15, "unexpected offset of execution_summary_message::fields_type::quantity");
static_assert(offsetof(execution_summary_message::fields_type, hidden_quantity) == 19, "unexpected offset of execution_summary_message::fields_type::hidden_quantity");
static_assert(offsetof(execution_summary_message::fields_type, stp_cancel_quantity) == 23, "unexpected offset of execution_summary_message::fields_type::stp_cancel_quantity");
static_assert(offsetof(execution_summary_message::fields_type, far_price) == 27, "unexpected offset of execution_summary_message::fields_type::far_price");
static_assert(offsetof(execution_summary_message::fields_type, add_quantity) == 31, "unexpected offset of execution_summary_message::fields_type::add_quantity");
static_assert(offsetof(execution_summary_message::fields_type, number_of_lit_executions) == 35, "unexpected offset of execution_summary_message::fields_type::number_of_lit_executions");
static_assert(sizeof(execution_summary_message::fields_type) == 37, "unexpected sizeof execution_summary_message::fields_type");
static_assert(sizeof(execution_summary_message) == sizeof(itch_totalview::message_header) + 37, "unexpected sizeof execution_summary_message");

#pragma pack(pop)
}
