#pragma once

#include "../types/ParticipantId.hpp"
#include "../types/TradeTotalVolume.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct ApproximateVolumeParticipant {

    ParticipantId participant_id;
    TradeTotalVolume trade_total_volume;

    // parse method
    static ApproximateVolumeParticipant* parse(std::byte* buffer) {
        return reinterpret_cast<ApproximateVolumeParticipant*>(buffer);
    }

    // parse method const
    static const ApproximateVolumeParticipant* parse(const std::byte* buffer) {
        return reinterpret_cast<const ApproximateVolumeParticipant*>(buffer);
    }
};

#pragma pack(pop)
}
