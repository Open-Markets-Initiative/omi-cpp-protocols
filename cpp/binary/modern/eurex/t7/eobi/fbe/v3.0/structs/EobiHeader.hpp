#pragma once

#include "../types/BodyLen.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MsgSeqNum.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

struct EobiHeader {

    BodyLen body_len;
    TemplateId template_id;
    MsgSeqNum msg_seq_num;

    // parse method
    static EobiHeader* parse(std::byte* buffer) {
        return reinterpret_cast<EobiHeader*>(buffer);
    }

    // parse method const
    static const EobiHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const EobiHeader*>(buffer);
    }
};

#pragma pack(pop)
}
