#pragma once

#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/AggressorIndicator.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct SecurityStatusWorkupGroup {

    OrderId order_id;
    Side side;
    AggressorIndicator aggressor_indicator;

    // parse method
    static SecurityStatusWorkupGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatusWorkupGroup*>(buffer);
    }

    // parse method const
    static const SecurityStatusWorkupGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatusWorkupGroup*>(buffer);
    }
};

#pragma pack(pop)
}
