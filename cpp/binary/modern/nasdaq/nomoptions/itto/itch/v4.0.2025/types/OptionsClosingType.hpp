#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Denotes which System Event is used to trigger the option closing process.
struct OptionsClosingType {

    static constexpr auto name = "Options Closing Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OptionsClosingType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionsClosingType(const char &value)
     : value{ value } {}

    // get value of OptionsClosingType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
