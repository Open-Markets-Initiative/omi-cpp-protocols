#pragma once

#include "../types/UnderlyingSecurityId.hpp"
#include "../types/UnderlyingSymbol.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

#pragma pack(push, 1)

struct UnderlyingsGroup {

    UnderlyingSecurityId underlying_security_id;
    UnderlyingSymbol underlying_symbol;

    // parse method
    static UnderlyingsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingsGroup*>(buffer);
    }

    // parse method const
    static const UnderlyingsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
