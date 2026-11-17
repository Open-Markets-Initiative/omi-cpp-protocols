// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/SecurityTypeText.hpp
#pragma once

#include <cstddef>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct SecurityTypeText {

    static constexpr auto name = "Security Type Text";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecurityTypeText()
     : value{} {}

    // standard constructor
    constexpr explicit SecurityTypeText(const type &value)
     : value{ value } {}

    // get value of SecurityTypeText field
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
