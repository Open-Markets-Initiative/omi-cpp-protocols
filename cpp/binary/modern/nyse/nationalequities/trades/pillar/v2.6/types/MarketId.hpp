#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// ID of the Originating Market.
struct MarketId {

    static constexpr const char* name = "Market Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MarketId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketId(const std::uint16_t value)
     : value{ value } {}

    // get value of MarketId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
