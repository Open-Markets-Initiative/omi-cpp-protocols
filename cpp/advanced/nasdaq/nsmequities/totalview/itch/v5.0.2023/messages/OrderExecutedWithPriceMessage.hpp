#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/ExecutedShares.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Printable.hpp"
#include "../types/ExecutionPrice.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Order Executed With Price Message
struct order_executed_with_price_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::executed_shares executed_shares;
        itch_totalview::match_number match_number;
        itch_totalview::printable printable;
        itch_totalview::execution_price execution_price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_with_price_message};

    fields_type fields;

    // parse method
    static order_executed_with_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_with_price_message*>(buffer);
    }

    // parse method const
    static const order_executed_with_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_with_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_with_price_message::fields_type, stock_locate) == 0, "unexpected offset of order_executed_with_price_message::fields_type::stock_locate");
static_assert(offsetof(order_executed_with_price_message::fields_type, tracking_number) == 2, "unexpected offset of order_executed_with_price_message::fields_type::tracking_number");
static_assert(offsetof(order_executed_with_price_message::fields_type, timestamp) == 4, "unexpected offset of order_executed_with_price_message::fields_type::timestamp");
static_assert(offsetof(order_executed_with_price_message::fields_type, order_reference_number) == 10, "unexpected offset of order_executed_with_price_message::fields_type::order_reference_number");
static_assert(offsetof(order_executed_with_price_message::fields_type, executed_shares) == 18, "unexpected offset of order_executed_with_price_message::fields_type::executed_shares");
static_assert(offsetof(order_executed_with_price_message::fields_type, match_number) == 22, "unexpected offset of order_executed_with_price_message::fields_type::match_number");
static_assert(offsetof(order_executed_with_price_message::fields_type, printable) == 30, "unexpected offset of order_executed_with_price_message::fields_type::printable");
static_assert(offsetof(order_executed_with_price_message::fields_type, execution_price) == 31, "unexpected offset of order_executed_with_price_message::fields_type::execution_price");
static_assert(sizeof(order_executed_with_price_message::fields_type) == 35, "unexpected sizeof order_executed_with_price_message::fields_type");
static_assert(sizeof(order_executed_with_price_message) == sizeof(message_header) + 35, "unexpected sizeof order_executed_with_price_message");

#pragma pack(pop)
}
