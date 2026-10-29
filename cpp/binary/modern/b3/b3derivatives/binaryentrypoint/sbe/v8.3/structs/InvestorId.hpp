#pragma once

#include "../types/Prefix.hpp"
#include "../types/Offset2Padding2.hpp"
#include "../types/Document.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct InvestorId {

    Prefix prefix;
    Offset2Padding2 offset_2_padding_2;
    Document document;

    // parse method
    static InvestorId* parse(std::byte* buffer) {
        return reinterpret_cast<InvestorId*>(buffer);
    }

    // parse method const
    static const InvestorId* parse(const std::byte* buffer) {
        return reinterpret_cast<const InvestorId*>(buffer);
    }
};

#pragma pack(pop)
}
