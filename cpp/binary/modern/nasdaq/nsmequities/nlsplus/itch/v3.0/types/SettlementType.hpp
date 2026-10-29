#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Settlement Type information
struct SettlementType {

    static constexpr auto name = "Settlement Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SettlementType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementType(const char &value)
     : value{ value } {}

    // get value of SettlementType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
