#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCode.hpp"
#include "../types/OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Operational Halt Message
struct operational_halt_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::stock stock;
        itch_totalview::market_code market_code;
        itch_totalview::operational_halt_action operational_halt_action;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::operational_halt_message};

    fields_type fields;

    // parse method
    static operational_halt_message* parse(std::byte* buffer) {
        return reinterpret_cast<operational_halt_message*>(buffer);
    }

    // parse method const
    static const operational_halt_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const operational_halt_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(operational_halt_message::fields_type, stock_locate) == 0, "unexpected offset of operational_halt_message::fields_type::stock_locate");
static_assert(offsetof(operational_halt_message::fields_type, tracking_number) == 2, "unexpected offset of operational_halt_message::fields_type::tracking_number");
static_assert(offsetof(operational_halt_message::fields_type, timestamp) == 4, "unexpected offset of operational_halt_message::fields_type::timestamp");
static_assert(offsetof(operational_halt_message::fields_type, stock) == 10, "unexpected offset of operational_halt_message::fields_type::stock");
static_assert(offsetof(operational_halt_message::fields_type, market_code) == 18, "unexpected offset of operational_halt_message::fields_type::market_code");
static_assert(offsetof(operational_halt_message::fields_type, operational_halt_action) == 19, "unexpected offset of operational_halt_message::fields_type::operational_halt_action");
static_assert(sizeof(operational_halt_message::fields_type) == 20, "unexpected sizeof operational_halt_message::fields_type");
static_assert(sizeof(operational_halt_message) == sizeof(message_header) + 20, "unexpected sizeof operational_halt_message");

#pragma pack(pop)
}
