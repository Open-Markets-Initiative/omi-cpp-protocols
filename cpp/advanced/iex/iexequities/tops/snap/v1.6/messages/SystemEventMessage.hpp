#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SystemEvent.hpp"
#include "../types/Timestamp.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

#pragma pack(push, 1)

// System Event Message
struct system_event_message {

    struct fields_type {
        snap_tops::system_event system_event;
        snap_tops::timestamp timestamp;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_tops::iex_tp_header) + sizeof(snap_tops::iex_tp_message_block_length) + sizeof(snap_tops::iex_tp_message_length) + sizeof(snap_tops::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_tops::iex_tp_header iex_tp_header;
    snap_tops::iex_tp_message_block_length iex_tp_message_block_length;
    snap_tops::iex_tp_message_length iex_tp_message_length;
    snap_tops::iex_tp_message_type iex_tp_message_type = snap_tops::iex_tp_message_type::enum_type::system_event_message;

    fields_type fields;

    // parse method
    static system_event_message* parse(std::byte* buffer) {
        return reinterpret_cast<system_event_message*>(buffer);
    }

    // parse method const
    static const system_event_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const system_event_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(system_event_message::fields_type, system_event) == 0, "unexpected offset of system_event_message::fields_type::system_event");
static_assert(offsetof(system_event_message::fields_type, timestamp) == 1, "unexpected offset of system_event_message::fields_type::timestamp");
static_assert(sizeof(system_event_message::fields_type) == 9, "unexpected sizeof system_event_message::fields_type");
static_assert(sizeof(system_event_message) == sizeof(message_header) + sizeof(snap_tops::iex_tp_header) + sizeof(snap_tops::iex_tp_message_block_length) + sizeof(snap_tops::iex_tp_message_length) + sizeof(snap_tops::iex_tp_message_type) + 9, "unexpected sizeof system_event_message");

#pragma pack(pop)
}
