#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Settlement Type information
struct CorrectedSettlementType {

    static constexpr auto name = "Corrected Settlement Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedSettlementType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedSettlementType(const char &value)
     : value{ value } {}

    // get value of CorrectedSettlementType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
