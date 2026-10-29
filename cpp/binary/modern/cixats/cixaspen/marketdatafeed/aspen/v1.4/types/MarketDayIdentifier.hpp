#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Unique identifier for trading day
struct MarketDayIdentifier {

    static constexpr auto name = "Market Day Identifier";
    static constexpr std::size_t size = 9;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr MarketDayIdentifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketDayIdentifier(const type &value)
     : value{ value } {}

    // get value of MarketDayIdentifier field
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
