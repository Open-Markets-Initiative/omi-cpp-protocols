#pragma once

#include "../types/BodyLen.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MsgSeqNum.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

struct MessageHeaderComp {

    BodyLen body_len;
    TemplateId template_id;
    MsgSeqNum msg_seq_num;

    // parse method
    static MessageHeaderComp* parse(std::byte* buffer) {
        return reinterpret_cast<MessageHeaderComp*>(buffer);
    }

    // parse method const
    static const MessageHeaderComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageHeaderComp*>(buffer);
    }
};

#pragma pack(pop)
}
