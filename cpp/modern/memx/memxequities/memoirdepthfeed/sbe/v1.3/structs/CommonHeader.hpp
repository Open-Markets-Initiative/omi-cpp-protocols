#pragma once

#include "../types/MessageType.hpp"
#include "../types/HeaderLength.hpp"
#include "../types/SessionId.hpp"
#include "../types/SequenceNumber.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

struct CommonHeader {

    MessageType message_type;
    HeaderLength header_length;
    SessionId session_id;
    SequenceNumber sequence_number;

    // parse method
    static CommonHeader* parse(std::byte* buffer) {
        return reinterpret_cast<CommonHeader*>(buffer);
    }

    // parse method const
    static const CommonHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const CommonHeader*>(buffer);
    }
};

#pragma pack(pop)
}
