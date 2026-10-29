#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Identifies Stream on which this symbol will be updated
struct StreamId {

    static constexpr const char* name = "Stream Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StreamId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StreamId(const std::uint16_t value)
     : value{ value } {}

    // get value of StreamId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
