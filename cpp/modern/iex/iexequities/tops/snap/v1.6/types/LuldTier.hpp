#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::snap::v1_6 {


// Indicates which Limit Up-Limit Down price band calculation parameter is to be used
struct LuldTier {

    static constexpr auto name = "Luld Tier";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LuldTier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LuldTier(const std::uint8_t &value)
     : value{ value } {}

    // get value of LuldTier field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
