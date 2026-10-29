#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Settlement Type information
struct OriginalSettlementType {

    static constexpr auto name = "Original Settlement Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalSettlementType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalSettlementType(const char &value)
     : value{ value } {}

    // get value of OriginalSettlementType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
