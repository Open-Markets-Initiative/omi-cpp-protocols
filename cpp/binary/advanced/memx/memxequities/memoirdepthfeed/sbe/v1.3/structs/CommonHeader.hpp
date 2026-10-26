#pragma once

#include <cstddef>
#include "../types/MessageType.hpp"
#include "../types/HeaderLength.hpp"
#include "../types/SessionId.hpp"
#include "../types/SequenceNumber.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

#pragma pack(push, 1)

struct common_header {

    sbe_memoirdepthfeed::message_type message_type;
    sbe_memoirdepthfeed::header_length header_length;
    sbe_memoirdepthfeed::session_id session_id;
    sbe_memoirdepthfeed::sequence_number sequence_number;

    // parse method
    static common_header* parse(std::byte* buffer) {
        return reinterpret_cast<common_header*>(buffer);
    }

    // parse method const
    static const common_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const common_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(common_header, message_type) == 0, "unexpected offset of common_header::message_type");
static_assert(offsetof(common_header, header_length) == 1, "unexpected offset of common_header::header_length");
static_assert(offsetof(common_header, session_id) == 2, "unexpected offset of common_header::session_id");
static_assert(offsetof(common_header, sequence_number) == 10, "unexpected offset of common_header::sequence_number");
static_assert(sizeof(common_header) == 18, "unexpected sizeof common_header");

#pragma pack(pop)
}
