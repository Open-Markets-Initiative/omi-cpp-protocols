#pragma once

#include "../types/LegSymbol.hpp"
#include "../types/LegRatio.hpp"
#include "../types/LegSecurityType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

struct ComplexInstrumentLeg {

    LegSymbol leg_symbol;
    LegRatio leg_ratio;
    LegSecurityType leg_security_type;

    // parse method
    static ComplexInstrumentLeg* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexInstrumentLeg*>(buffer);
    }

    // parse method const
    static const ComplexInstrumentLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexInstrumentLeg*>(buffer);
    }
};

#pragma pack(pop)
}
