#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Root symbol for options in OCC symbology (EX. BRKB)
struct OptionSymbolRoot {

    static constexpr auto name = "Option Symbol Root";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr OptionSymbolRoot()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionSymbolRoot(const type &value)
     : value{ value } {}

    // get value of OptionSymbolRoot field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
