#pragma once

#include "../types/SummaryMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

struct SummaryMessage {

    SummaryMessageType summary_message_type;

    // parse method
    static SummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SummaryMessage*>(buffer);
    }

    // parse method const
    static const SummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SummaryMessage*>(buffer);
    }
};

#pragma pack(pop)
}
