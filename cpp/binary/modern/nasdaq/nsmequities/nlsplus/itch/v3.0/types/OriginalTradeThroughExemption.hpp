#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Sec Regulation Nms Trade Through Exemption codes
struct OriginalTradeThroughExemption {

    static constexpr auto name = "Original Trade Through Exemption";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalTradeThroughExemption()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalTradeThroughExemption(const char &value)
     : value{ value } {}

    // get value of OriginalTradeThroughExemption field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
