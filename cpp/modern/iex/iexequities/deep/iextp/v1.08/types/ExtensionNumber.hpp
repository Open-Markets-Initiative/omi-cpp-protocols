#pragma once

#include <cstddef>

namespace iex::iexequities::deep::iextp::v1_08 {


// Number of extensions an auction received
struct ExtensionNumber {

    static constexpr auto name = "Extension Number";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExtensionNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExtensionNumber(const char &value)
     : value{ value } {}

    // get value of ExtensionNumber field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
