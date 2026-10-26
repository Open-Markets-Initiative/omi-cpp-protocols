#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Strike price. ASCII 0-9 with optional decimal point. EG:51.75, 123 (Option only)
struct StrikePrice {

    static constexpr auto name = "Strike Price";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr StrikePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePrice(const type &value)
     : value{ value } {}

    // get value of StrikePrice field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
