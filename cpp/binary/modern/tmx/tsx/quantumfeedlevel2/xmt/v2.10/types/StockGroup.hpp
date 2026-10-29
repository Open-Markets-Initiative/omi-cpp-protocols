#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// An Identifier Of The Stock Group
struct StockGroup {

    static constexpr auto name = "Stock Group";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr StockGroup()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StockGroup(const std::uint8_t &value)
     : value{ value } {}

    // get value of StockGroup field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
