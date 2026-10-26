#pragma once

#include "../types/ParticipantId.hpp"
#include "../types/FractionalTradeTotalVolume.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct Participant {

    ParticipantId participant_id;
    FractionalTradeTotalVolume fractional_trade_total_volume;

    // parse method
    static Participant* parse(std::byte* buffer) {
        return reinterpret_cast<Participant*>(buffer);
    }

    // parse method const
    static const Participant* parse(const std::byte* buffer) {
        return reinterpret_cast<const Participant*>(buffer);
    }
};

#pragma pack(pop)
}
