#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Total quantity of customer orders at the Ask price
struct AskCustomerVolume {

    static constexpr const char* name = "Ask Customer Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskCustomerVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of AskCustomerVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
