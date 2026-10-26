#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The number of shares executed
struct ExecutedShares {

    static constexpr const char* name = "Executed Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecutedShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecutedShares(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExecutedShares field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
