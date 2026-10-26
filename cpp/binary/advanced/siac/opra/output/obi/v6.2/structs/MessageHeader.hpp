#pragma once

#include <cstddef>
#include "../types/ParticipantId.hpp"
#include "../types/MessageCategory.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct message_header {

    obi_output::participant_id participant_id;
    obi_output::message_category message_category;

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
static_assert(offsetof(message_header, participant_id) == 0, "unexpected offset of message_header::participant_id");
static_assert(offsetof(message_header, message_category) == 1, "unexpected offset of message_header::message_category");
static_assert(sizeof(message_header) == 2, "unexpected sizeof message_header");

#pragma pack(pop)
}
