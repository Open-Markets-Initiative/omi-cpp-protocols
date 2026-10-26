#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {


// Number of extensions an auction received
struct ExtensionNumber {

    static constexpr auto name = "Extension Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExtensionNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExtensionNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExtensionNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
