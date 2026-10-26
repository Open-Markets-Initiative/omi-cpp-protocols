#pragma once

#include "../types/SecurityId.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct SecurityListRequestRelatedSymbolGroup {

    SecurityId security_id;

    // parse method
    static SecurityListRequestRelatedSymbolGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityListRequestRelatedSymbolGroup*>(buffer);
    }

    // parse method const
    static const SecurityListRequestRelatedSymbolGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityListRequestRelatedSymbolGroup*>(buffer);
    }
};

#pragma pack(pop)
}
