#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Unix time (number of seconds since 1970-01-01 00:00:00 UTC).
struct Second {

    static constexpr const char* name = "Second";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Second()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Second(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Second field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
