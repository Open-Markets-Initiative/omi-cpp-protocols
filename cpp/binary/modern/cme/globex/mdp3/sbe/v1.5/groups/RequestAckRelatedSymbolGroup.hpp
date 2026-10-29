#pragma once

#include "../types/SecurityId.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct RequestAckRelatedSymbolGroup {

    SecurityId security_id;

    // parse method
    static RequestAckRelatedSymbolGroup* parse(std::byte* buffer) {
        return reinterpret_cast<RequestAckRelatedSymbolGroup*>(buffer);
    }

    // parse method const
    static const RequestAckRelatedSymbolGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestAckRelatedSymbolGroup*>(buffer);
    }
};

#pragma pack(pop)
}
