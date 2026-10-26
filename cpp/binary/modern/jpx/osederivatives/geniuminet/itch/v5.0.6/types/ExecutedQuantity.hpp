#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// The quantity being executed
struct ExecutedQuantity {

    static constexpr const char* name = "Executed Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ExecutedQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecutedQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExecutedQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
