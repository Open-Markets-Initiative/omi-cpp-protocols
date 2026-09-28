#pragma once

#include "../types/UrlLinkLength.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

#pragma pack(push, 1)

struct UrlLink {

    UrlLinkLength url_link_length;

    // parse method
    static UrlLink* parse(std::byte* buffer) {
        return reinterpret_cast<UrlLink*>(buffer);
    }

    // parse method const
    static const UrlLink* parse(const std::byte* buffer) {
        return reinterpret_cast<const UrlLink*>(buffer);
    }
};

#pragma pack(pop)
}
