#pragma once

#include <cstddef>
#include "../types/BodyLen.hpp"
#include "../types/TemplateId.hpp"
#include "../types/MsgSeqNum.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

struct eobi_header {

    fbe_eobi::body_len body_len;
    fbe_eobi::template_id template_id;
    fbe_eobi::msg_seq_num msg_seq_num;

    // parse method
    static eobi_header* parse(std::byte* buffer) {
        return reinterpret_cast<eobi_header*>(buffer);
    }

    // parse method const
    static const eobi_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const eobi_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(eobi_header, body_len) == 0, "unexpected offset of eobi_header::body_len");
static_assert(offsetof(eobi_header, template_id) == 2, "unexpected offset of eobi_header::template_id");
static_assert(offsetof(eobi_header, msg_seq_num) == 4, "unexpected offset of eobi_header::msg_seq_num");
static_assert(sizeof(eobi_header) == 8, "unexpected sizeof eobi_header");

#pragma pack(pop)
}
