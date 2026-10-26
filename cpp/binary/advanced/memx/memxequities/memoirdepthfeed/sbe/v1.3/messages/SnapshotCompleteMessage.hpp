#pragma once

#include <cstddef>
#include "../structs/SbeHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/AsOfSequenceNumber.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

// Snapshot Complete Message
struct snapshot_complete_message {

    struct fields_type {
        sbe_memoirdepthfeed::timestamp timestamp;
        sbe_memoirdepthfeed::as_of_sequence_number as_of_sequence_number;
    };

    sbe_memoirdepthfeed::sbe_header header = {{}, template_id::enum_type::snapshot_complete_message, schema_id(2), version(259)};

    fields_type fields;

    // parse method
    static snapshot_complete_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_complete_message*>(buffer);
    }

    // parse method const
    static const snapshot_complete_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_complete_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_complete_message::fields_type, timestamp) == 0, "unexpected offset of snapshot_complete_message::fields_type::timestamp");
static_assert(offsetof(snapshot_complete_message::fields_type, as_of_sequence_number) == 8, "unexpected offset of snapshot_complete_message::fields_type::as_of_sequence_number");
static_assert(sizeof(snapshot_complete_message::fields_type) == 16, "unexpected sizeof snapshot_complete_message::fields_type");
static_assert(sizeof(snapshot_complete_message) == sizeof(sbe_memoirdepthfeed::sbe_header) + 16, "unexpected sizeof snapshot_complete_message");

#pragma pack(pop)
}
