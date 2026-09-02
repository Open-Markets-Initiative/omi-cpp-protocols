#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;


#pragma pack(push, 1)

// Snapshot Data Message
struct snapshot_data_message {

    struct fields_type {
        snap_tops::iex_tp_header iex_tp_header;
        snap_tops::iex_tp_message_block_length iex_tp_message_block_length;
        snap_tops::iex_tp_message_length iex_tp_message_length;
        snap_tops::iex_tp_message_type iex_tp_message_type;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::snapshot_data_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return (sz + 2) == sizeof(message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_var_data iex_tp_message_data() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static snapshot_data_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_data_message*>(buffer);
    }

    // parse method const
    static const snapshot_data_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_data_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_data_message::fields_type, iex_tp_header) == 0, "unexpected offset of snapshot_data_message::fields_type::iex_tp_header");
static_assert(offsetof(snapshot_data_message::fields_type, iex_tp_message_block_length) == 1, "unexpected offset of snapshot_data_message::fields_type::iex_tp_message_block_length");
static_assert(offsetof(snapshot_data_message::fields_type, iex_tp_message_length) == 3, "unexpected offset of snapshot_data_message::fields_type::iex_tp_message_length");
static_assert(offsetof(snapshot_data_message::fields_type, iex_tp_message_type) == 5, "unexpected offset of snapshot_data_message::fields_type::iex_tp_message_type");
static_assert(sizeof(snapshot_data_message::fields_type) == 6, "unexpected sizeof snapshot_data_message::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotDataMessageWriter.hpp"
#include "details/SnapshotDataMessageReader.hpp"
