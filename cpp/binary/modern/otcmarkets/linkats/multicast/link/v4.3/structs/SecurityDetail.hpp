// OtcMarkets.LinkAts.Multicast.Link.v4.3: structs/SecurityDetail.hpp
#pragma once

#include "../types/SecurityDetailSize.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

struct SecurityDetail {

    SecurityDetailSize security_detail_size;

    // parse method
    static SecurityDetail* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityDetail*>(buffer);
    }

    // parse method const
    static const SecurityDetail* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityDetail*>(buffer);
    }
};

#pragma pack(pop)
}
