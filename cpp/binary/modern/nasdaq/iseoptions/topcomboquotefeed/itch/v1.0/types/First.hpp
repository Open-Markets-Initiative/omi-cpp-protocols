#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Opening price for the day
struct First {

    static constexpr const char* name = "First";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr First()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit First(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of First field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
