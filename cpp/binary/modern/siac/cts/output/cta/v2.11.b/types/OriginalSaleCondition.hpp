#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cts::output::cta::v2_11_b {


// Original sale condition associated with a trade
struct OriginalSaleCondition {

    static constexpr auto name = "Original Sale Condition";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr OriginalSaleCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalSaleCondition(const type &value)
     : value{ value } {}

    // get value of OriginalSaleCondition field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
