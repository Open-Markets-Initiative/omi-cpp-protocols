#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OperationalHaltStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

namespace snap_deep = ::iex::iexequities::deep::snap::v1_6;

#pragma pack(push, 1)

// Operational Halt Status Message
struct operational_halt_status_message {

    struct fields_type {
        snap_deep::operational_halt_status operational_halt_status;
        snap_deep::timestamp timestamp;
        snap_deep::symbol symbol;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), {}};

    fields_type fields;

    // parse method
    static operational_halt_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<operational_halt_status_message*>(buffer);
    }

    // parse method const
    static const operational_halt_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const operational_halt_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(operational_halt_status_message::fields_type, operational_halt_status) == 0, "unexpected offset of operational_halt_status_message::fields_type::operational_halt_status");
static_assert(offsetof(operational_halt_status_message::fields_type, timestamp) == 1, "unexpected offset of operational_halt_status_message::fields_type::timestamp");
static_assert(offsetof(operational_halt_status_message::fields_type, symbol) == 9, "unexpected offset of operational_halt_status_message::fields_type::symbol");
static_assert(sizeof(operational_halt_status_message::fields_type) == 17, "unexpected sizeof operational_halt_status_message::fields_type");
static_assert(sizeof(operational_halt_status_message) == sizeof(message_header) + 17, "unexpected sizeof operational_halt_status_message");

#pragma pack(pop)
}
