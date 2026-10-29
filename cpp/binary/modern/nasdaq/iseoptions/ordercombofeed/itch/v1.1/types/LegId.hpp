#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Leg identifier within this strategy. This is an exchange-assigned 0-based index. E.g. Nth leg has LegId=N-1.
struct LegId {

    static constexpr auto name = "Leg Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LegId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegId(const std::uint8_t &value)
     : value{ value } {}

    // get value of LegId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
