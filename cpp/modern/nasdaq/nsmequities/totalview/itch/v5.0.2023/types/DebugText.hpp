#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Free form human readable text
struct DebugText {

    static constexpr auto name = "Debug Text";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr DebugText()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DebugText(const char &value)
     : value{ value } {}

    // get value of DebugText field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
