#pragma once

#include "../types/ControlFields.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

struct ChallengeRequest {

    ControlFields control_fields;

    // parse method
    static ChallengeRequest* parse(std::byte* buffer) {
        return reinterpret_cast<ChallengeRequest*>(buffer);
    }

    // parse method const
    static const ChallengeRequest* parse(const std::byte* buffer) {
        return reinterpret_cast<const ChallengeRequest*>(buffer);
    }
};

#pragma pack(pop)
}
