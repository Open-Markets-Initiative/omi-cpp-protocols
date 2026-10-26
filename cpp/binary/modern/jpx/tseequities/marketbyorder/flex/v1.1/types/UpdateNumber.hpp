#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Per issue update number assigned from 1 each business day
struct UpdateNumber {

    static constexpr const char* name = "Update Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UpdateNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UpdateNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of UpdateNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
