#pragma once

#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Total packet count within a multi packet split set always 0 in arrowhead4 0
struct TotalNumberOfPackets {

    static constexpr auto name = "Total Number Of Packets";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TotalNumberOfPackets()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalNumberOfPackets(const std::uint8_t &value)
     : value{ value } {}

    // get value of TotalNumberOfPackets field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
