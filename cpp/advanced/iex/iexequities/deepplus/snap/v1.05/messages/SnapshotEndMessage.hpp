#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SnapshotSequenceNumber.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

// Snapshot End Message
struct snapshot_end_message {

    struct fields_type {
        snap_deepplus::snapshot_sequence_number snapshot_sequence_number;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::snapshot_end_message};

    fields_type fields;

    // parse method
    static snapshot_end_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_end_message*>(buffer);
    }

    // parse method const
    static const snapshot_end_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_end_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_end_message::fields_type, snapshot_sequence_number) == 0, "unexpected offset of snapshot_end_message::fields_type::snapshot_sequence_number");
static_assert(sizeof(snapshot_end_message::fields_type) == 8, "unexpected sizeof snapshot_end_message::fields_type");
static_assert(sizeof(snapshot_end_message) == sizeof(message_header) + 8, "unexpected sizeof snapshot_end_message");

#pragma pack(pop)
}
