#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {


// Trading Action reason
struct TradingActionReason {

    static constexpr auto name = "Trading Action Reason";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr TradingActionReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingActionReason(const type &value)
     : value{ value } {}

    // get value of TradingActionReason field
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
