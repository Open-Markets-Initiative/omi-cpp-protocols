#pragma once

#include <cstddef>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Option Type value
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
