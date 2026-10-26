#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// 
struct OptionType {

    static constexpr auto name = "Option Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OptionType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionType(const char &value)
     : value{ value } {}

    // get value of OptionType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
