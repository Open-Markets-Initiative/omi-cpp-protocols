#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Blank filled. Not available for ASX 24 products.
struct BasisOfQuotation {

    static constexpr auto name = "Basis Of Quotation";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr BasisOfQuotation()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BasisOfQuotation(const type &value)
     : value{ value } {}

    // get value of BasisOfQuotation field
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
