#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Volume of the trade in actual number of contracts
struct Volume4 {

    static constexpr const char* name = "Volume 4";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Volume4()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Volume4(const std::uint32_t value)
     : value{ value } {}

    // get value of Volume4 field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
