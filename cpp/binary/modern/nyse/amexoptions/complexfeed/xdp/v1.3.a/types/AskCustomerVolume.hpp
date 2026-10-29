#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Total quantity of ‘Customer’ orders available at the above Ask price.
struct AskCustomerVolume {

    static constexpr const char* name = "Ask Customer Volume";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr AskCustomerVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskCustomerVolume(const std::uint16_t value)
     : value{ value } {}

    // get value of AskCustomerVolume field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
