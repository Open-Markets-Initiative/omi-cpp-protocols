#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Sec Regulation Nms Trade Through Exemption codes
struct TradeThroughExemption {

    static constexpr auto name = "Trade Through Exemption";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeThroughExemption()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeThroughExemption(const char &value)
     : value{ value } {}

    // get value of TradeThroughExemption field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
