#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// For retransmission set to the number of times the system has been rebooted; for snapshot set to 0
struct NumberOfSystemReboots {

    static constexpr auto name = "Number Of System Reboots";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfSystemReboots()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfSystemReboots(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfSystemReboots field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
