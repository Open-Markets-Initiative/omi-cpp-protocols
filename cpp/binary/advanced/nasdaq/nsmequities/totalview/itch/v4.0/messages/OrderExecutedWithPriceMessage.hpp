#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/ExecutedShares.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Printable.hpp"
#include "../types/ExecutionPrice.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Order Executed With Price Message
struct order_executed_with_price_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::executed_shares executed_shares;
        itch_totalview::match_number match_number;
        itch_totalview::printable printable;
        itch_totalview::execution_price execution_price;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_with_price_message};

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
static_assert(offsetof(order_executed_with_price_message::fields_type, nanoseconds) == 0, "unexpected offset of order_executed_with_price_message::fields_type::nanoseconds");
static_assert(offsetof(order_executed_with_price_message::fields_type, order_reference_number) == 4, "unexpected offset of order_executed_with_price_message::fields_type::order_reference_number");
static_assert(offsetof(order_executed_with_price_message::fields_type, executed_shares) == 12, "unexpected offset of order_executed_with_price_message::fields_type::executed_shares");
static_assert(offsetof(order_executed_with_price_message::fields_type, match_number) == 16, "unexpected offset of order_executed_with_price_message::fields_type::match_number");
static_assert(offsetof(order_executed_with_price_message::fields_type, printable) == 24, "unexpected offset of order_executed_with_price_message::fields_type::printable");
static_assert(offsetof(order_executed_with_price_message::fields_type, execution_price) == 25, "unexpected offset of order_executed_with_price_message::fields_type::execution_price");
static_assert(sizeof(order_executed_with_price_message::fields_type) == 29, "unexpected sizeof order_executed_with_price_message::fields_type");
static_assert(sizeof(order_executed_with_price_message) == sizeof(itch_totalview::message_header) + 29, "unexpected sizeof order_executed_with_price_message");

#pragma pack(pop)
}
