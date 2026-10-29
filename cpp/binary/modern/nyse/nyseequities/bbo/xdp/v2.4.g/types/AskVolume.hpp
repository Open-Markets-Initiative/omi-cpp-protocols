#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// The aggregate round lot size at the ask price, in shares.
struct AskVolume {

    static constexpr const char* name = "Ask Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of AskVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
