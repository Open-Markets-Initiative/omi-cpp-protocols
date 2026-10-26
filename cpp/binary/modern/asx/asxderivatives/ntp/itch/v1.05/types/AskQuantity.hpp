#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Total Ask Quantity available for execution.
struct AskQuantity {

    static constexpr const char* name = "Ask Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AskQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
