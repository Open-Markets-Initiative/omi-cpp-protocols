#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates if the security is eligible to be released for trading
struct OpenEligibilityStatus {

    static constexpr auto name = "Open Eligibility Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpenEligibilityStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenEligibilityStatus(const char &value)
     : value{ value } {}

    // get value of OpenEligibilityStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
