#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {


// The number of messages in this packet
struct NumberMsgs {

    static constexpr auto name = "Number Msgs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberMsgs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberMsgs(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberMsgs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
