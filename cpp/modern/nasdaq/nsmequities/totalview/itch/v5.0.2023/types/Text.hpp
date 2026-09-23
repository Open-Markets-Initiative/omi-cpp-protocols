#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Free form human readable text
struct Text {

    static constexpr auto name = "Text";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Text()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Text(const char &value)
     : value{ value } {}

    // get value of Text field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
