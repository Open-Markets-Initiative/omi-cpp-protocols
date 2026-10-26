#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Number of open contracts at EOD for the specified VOI Trade Date.
struct OpenInterest {

    static constexpr const char* name = "Open Interest";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OpenInterest()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenInterest(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OpenInterest field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
