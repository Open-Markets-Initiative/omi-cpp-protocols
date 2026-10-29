#pragma once

#include <cstddef>
#include "../types/BodyLen.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MsgSeqNum.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

struct message_header_comp {

    fbe_eobi::body_len body_len;
    fbe_eobi::template_id template_id;
    fbe_eobi::msg_seq_num msg_seq_num;

    // parse method
    static message_header_comp* parse(std::byte* buffer) {
        return reinterpret_cast<message_header_comp*>(buffer);
    }

    // parse method const
    static const message_header_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header_comp, body_len) == 0, "unexpected offset of message_header_comp::body_len");
static_assert(offsetof(message_header_comp, template_id) == 2, "unexpected offset of message_header_comp::template_id");
static_assert(offsetof(message_header_comp, msg_seq_num) == 4, "unexpected offset of message_header_comp::msg_seq_num");
static_assert(sizeof(message_header_comp) == 8, "unexpected sizeof message_header_comp");

#pragma pack(pop)
}
