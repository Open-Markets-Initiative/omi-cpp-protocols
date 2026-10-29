#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {


// ID of the Originating matching engine server.
struct SystemId {

    static constexpr auto name = "System Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SystemId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SystemId(const std::uint8_t &value)
     : value{ value } {}

    // get value of SystemId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
