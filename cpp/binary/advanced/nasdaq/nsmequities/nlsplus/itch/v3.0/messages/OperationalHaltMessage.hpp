#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCode.hpp"
#include "../types/OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Operational Halt Message
struct operational_halt_message {

    struct fields_type {
        itch_nlsplus::stock stock;
        itch_nlsplus::market_code market_code;
        itch_nlsplus::operational_halt_action operational_halt_action;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::operational_halt_message};

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
static_assert(offsetof(operational_halt_message::fields_type, stock) == 0, "unexpected offset of operational_halt_message::fields_type::stock");
static_assert(offsetof(operational_halt_message::fields_type, market_code) == 8, "unexpected offset of operational_halt_message::fields_type::market_code");
static_assert(offsetof(operational_halt_message::fields_type, operational_halt_action) == 9, "unexpected offset of operational_halt_message::fields_type::operational_halt_action");
static_assert(sizeof(operational_halt_message::fields_type) == 10, "unexpected sizeof operational_halt_message::fields_type");
static_assert(sizeof(operational_halt_message) == sizeof(itch_nlsplus::message_header) + 10, "unexpected sizeof operational_halt_message");

#pragma pack(pop)
}
