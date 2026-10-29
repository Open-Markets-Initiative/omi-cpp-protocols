#pragma once

#include <cstddef>
#include "../types/BodyLen.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MsgSeqNum.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

struct message_header {

    fbe_eobi::body_len body_len;
    fbe_eobi::template_id template_id;
    fbe_eobi::msg_seq_num msg_seq_num;

    // parse method
    static message_header* parse(std::byte* buffer) {
        return reinterpret_cast<message_header*>(buffer);
    }

    // parse method const
    static const message_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header, body_len) == 0, "unexpected offset of message_header::body_len");
static_assert(offsetof(message_header, template_id) == 2, "unexpected offset of message_header::template_id");
static_assert(offsetof(message_header, msg_seq_num) == 4, "unexpected offset of message_header::msg_seq_num");
static_assert(sizeof(message_header) == 8, "unexpected sizeof message_header");

#pragma pack(pop)
}
