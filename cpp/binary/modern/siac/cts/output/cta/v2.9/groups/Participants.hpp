#pragma once

#include "../types/ParticipantId.hpp"
#include "../types/TradeTotalVolume.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

struct Participants {

    ParticipantId participant_id;
    TradeTotalVolume trade_total_volume;

    // parse method
    static Participants* parse(std::byte* buffer) {
        return reinterpret_cast<Participants*>(buffer);
    }

    // parse method const
    static const Participants* parse(const std::byte* buffer) {
        return reinterpret_cast<const Participants*>(buffer);
    }
};

#pragma pack(pop)
}
