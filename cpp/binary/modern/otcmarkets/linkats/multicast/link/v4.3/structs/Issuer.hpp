// OtcMarkets.LinkAts.Multicast.Link.v4.3: structs/Issuer.hpp
#pragma once

#include "../types/IssuerSize.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

struct Issuer {

    IssuerSize issuer_size;

    // parse method
    static Issuer* parse(std::byte* buffer) {
        return reinterpret_cast<Issuer*>(buffer);
    }

    // parse method const
    static const Issuer* parse(const std::byte* buffer) {
        return reinterpret_cast<const Issuer*>(buffer);
    }
};

#pragma pack(pop)
}
