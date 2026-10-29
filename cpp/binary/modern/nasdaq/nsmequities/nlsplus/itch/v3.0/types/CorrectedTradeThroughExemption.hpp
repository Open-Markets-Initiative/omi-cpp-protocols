#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Sec Regulation Nms Trade Through Exemption codes
struct CorrectedTradeThroughExemption {

    static constexpr auto name = "Corrected Trade Through Exemption";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedTradeThroughExemption()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedTradeThroughExemption(const char &value)
     : value{ value } {}

    // get value of CorrectedTradeThroughExemption field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
