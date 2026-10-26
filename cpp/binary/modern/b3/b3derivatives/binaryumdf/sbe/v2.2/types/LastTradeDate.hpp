#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// lastTradeDate
struct LastTradeDate {

    static constexpr const char* name = "Last Trade Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr LastTradeDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastTradeDate(const std::uint16_t value)
     : value{ value } {}

    // get value of LastTradeDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
