#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OperationalHaltStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

// Operational Halt Status Message
struct operational_halt_status_message {

    struct fields_type {
        snap_deepplus::operational_halt_status operational_halt_status;
        snap_deepplus::timestamp timestamp;
        snap_deepplus::symbol symbol;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_deepplus::iex_tp_header) + sizeof(snap_deepplus::iex_tp_message_block_length) + sizeof(snap_deepplus::iex_tp_message_length) + sizeof(snap_deepplus::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_deepplus::iex_tp_header iex_tp_header;
    snap_deepplus::iex_tp_message_block_length iex_tp_message_block_length;
    snap_deepplus::iex_tp_message_length iex_tp_message_length;
    snap_deepplus::iex_tp_message_type iex_tp_message_type = snap_deepplus::iex_tp_message_type::enum_type::operational_halt_status_message;

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
static_assert(sizeof(operational_halt_status_message) == sizeof(message_header) + sizeof(snap_deepplus::iex_tp_header) + sizeof(snap_deepplus::iex_tp_message_block_length) + sizeof(snap_deepplus::iex_tp_message_length) + sizeof(snap_deepplus::iex_tp_message_type) + 17, "unexpected sizeof operational_halt_status_message");

#pragma pack(pop)
}
