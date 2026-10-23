#pragma once

#include "../types/SecurityId.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct SecurityStatusRequestRelatedSymbolGroup {

    SecurityId security_id;

    // parse method
    static SecurityStatusRequestRelatedSymbolGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatusRequestRelatedSymbolGroup*>(buffer);
    }

    // parse method const
    static const SecurityStatusRequestRelatedSymbolGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatusRequestRelatedSymbolGroup*>(buffer);
    }
};

#pragma pack(pop)
}
