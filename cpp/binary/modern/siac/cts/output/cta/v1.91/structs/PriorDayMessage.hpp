#pragma once

#include "../types/PriorDayMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct PriorDayMessage {

    PriorDayMessageType prior_day_message_type;

    // parse method
    static PriorDayMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriorDayMessage*>(buffer);
    }

    // parse method const
    static const PriorDayMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriorDayMessage*>(buffer);
    }
};

#pragma pack(pop)
}
