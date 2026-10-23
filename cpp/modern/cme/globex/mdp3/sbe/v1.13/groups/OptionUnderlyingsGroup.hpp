#pragma once

#include "../types/UnderlyingSecurityId.hpp"
#include "../types/UnderlyingSymbol.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct OptionUnderlyingsGroup {

    UnderlyingSecurityId underlying_security_id;
    UnderlyingSymbol underlying_symbol;

    // parse method
    static OptionUnderlyingsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<OptionUnderlyingsGroup*>(buffer);
    }

    // parse method const
    static const OptionUnderlyingsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionUnderlyingsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
