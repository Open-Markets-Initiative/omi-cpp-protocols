#pragma once

#include <cstddef>
#include "../types/MessageLength.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MessageType.hpp"
#include "../types/MsgSeqNum.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct message_header {

    csm_marketdatafeed::message_length message_length;
    csm_marketdatafeed::template_id template_id;
    csm_marketdatafeed::message_type message_type;
    csm_marketdatafeed::msg_seq_num msg_seq_num;

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
static_assert(offsetof(message_header, message_length) == 0, "unexpected offset of message_header::message_length");
static_assert(offsetof(message_header, template_id) == 2, "unexpected offset of message_header::template_id");
static_assert(offsetof(message_header, message_type) == 3, "unexpected offset of message_header::message_type");
static_assert(offsetof(message_header, msg_seq_num) == 4, "unexpected offset of message_header::msg_seq_num");
static_assert(sizeof(message_header) == 8, "unexpected sizeof message_header");

#pragma pack(pop)
}
