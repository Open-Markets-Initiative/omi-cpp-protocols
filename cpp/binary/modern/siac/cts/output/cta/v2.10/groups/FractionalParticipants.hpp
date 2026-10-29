#pragma once

#include "../types/ParticipantId.hpp"
#include "../types/FractionalTradeTotalVolume.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct FractionalParticipants {

    ParticipantId participant_id;
    FractionalTradeTotalVolume fractional_trade_total_volume;

    // parse method
    static FractionalParticipants* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalParticipants*>(buffer);
    }

    // parse method const
    static const FractionalParticipants* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalParticipants*>(buffer);
    }
};

#pragma pack(pop)
}
