#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/Pad4.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Heartbeat Message
struct heartbeat_message {

    struct fields_type {
        fbe_eobi::last_msg_seq_num_processed last_msg_seq_num_processed;
        fbe_eobi::pad_4 pad_4;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::heartbeat_message, {}};

    fields_type fields;

    // parse method
    static heartbeat_message* parse(std::byte* buffer) {
        return reinterpret_cast<heartbeat_message*>(buffer);
    }

    // parse method const
    static const heartbeat_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const heartbeat_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(heartbeat_message::fields_type, last_msg_seq_num_processed) == 0, "unexpected offset of heartbeat_message::fields_type::last_msg_seq_num_processed");
static_assert(offsetof(heartbeat_message::fields_type, pad_4) == 4, "unexpected offset of heartbeat_message::fields_type::pad_4");
static_assert(sizeof(heartbeat_message::fields_type) == 8, "unexpected sizeof heartbeat_message::fields_type");
static_assert(sizeof(heartbeat_message) == sizeof(fbe_eobi::message_header) + 8, "unexpected sizeof heartbeat_message");

#pragma pack(pop)
}
