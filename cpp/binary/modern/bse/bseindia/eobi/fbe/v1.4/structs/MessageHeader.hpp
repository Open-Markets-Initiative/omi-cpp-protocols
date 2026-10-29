#pragma once

#include "../types/BodyLen.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MsgSeqNum.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

struct MessageHeader {

    BodyLen body_len;
    TemplateId template_id;
    MsgSeqNum msg_seq_num;

    // parse method
    static MessageHeader* parse(std::byte* buffer) {
        return reinterpret_cast<MessageHeader*>(buffer);
    }

    // parse method const
    static const MessageHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageHeader*>(buffer);
    }
};

#pragma pack(pop)
}
