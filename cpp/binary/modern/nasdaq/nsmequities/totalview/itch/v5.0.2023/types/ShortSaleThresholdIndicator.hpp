#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates if a security is subject to mandatory close-out of short sales under SEC Rule 203(b)(3).
struct ShortSaleThresholdIndicator {

    static constexpr auto name = "Short Sale Threshold Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ShortSaleThresholdIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSaleThresholdIndicator(const char &value)
     : value{ value } {}

    // get value of ShortSaleThresholdIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
