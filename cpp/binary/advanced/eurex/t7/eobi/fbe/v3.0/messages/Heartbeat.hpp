#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/Pad4.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Heartbeat
struct heartbeat {

    struct fields_type {
        fbe_eobi::last_msg_seq_num_processed last_msg_seq_num_processed;
        fbe_eobi::pad4 pad4;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::heartbeat, {}};

    fields_type fields;

    // parse method
    static heartbeat* parse(std::byte* buffer) {
        return reinterpret_cast<heartbeat*>(buffer);
    }

    // parse method const
    static const heartbeat* parse(const std::byte* buffer) {
        return reinterpret_cast<const heartbeat*>(buffer);
    }

};

// layout verification
static_assert(offsetof(heartbeat::fields_type, last_msg_seq_num_processed) == 0, "unexpected offset of heartbeat::fields_type::last_msg_seq_num_processed");
static_assert(offsetof(heartbeat::fields_type, pad4) == 4, "unexpected offset of heartbeat::fields_type::pad4");
static_assert(sizeof(heartbeat::fields_type) == 8, "unexpected sizeof heartbeat::fields_type");
static_assert(sizeof(heartbeat) == sizeof(fbe_eobi::message_header_comp) + 8, "unexpected sizeof heartbeat");

#pragma pack(pop)
}
