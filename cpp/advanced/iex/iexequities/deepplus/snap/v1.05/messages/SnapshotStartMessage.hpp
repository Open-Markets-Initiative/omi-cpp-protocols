#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SnapshotLength.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

// Snapshot Start Message
struct snapshot_start_message {

    struct fields_type {
        snap_deepplus::snapshot_length snapshot_length;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::snapshot_start_message};

    fields_type fields;

    // parse method
    static snapshot_start_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_start_message*>(buffer);
    }

    // parse method const
    static const snapshot_start_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_start_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_start_message::fields_type, snapshot_length) == 0, "unexpected offset of snapshot_start_message::fields_type::snapshot_length");
static_assert(sizeof(snapshot_start_message::fields_type) == 8, "unexpected sizeof snapshot_start_message::fields_type");
static_assert(sizeof(snapshot_start_message) == sizeof(message_header) + 8, "unexpected sizeof snapshot_start_message");

#pragma pack(pop)
}
