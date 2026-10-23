#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cts::output::cta::v2_11_b {


// Corrected sale condition associated with a trade
struct CorrectedSaleCondition {

    static constexpr auto name = "Corrected Sale Condition";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr CorrectedSaleCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedSaleCondition(const type &value)
     : value{ value } {}

    // get value of CorrectedSaleCondition field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
