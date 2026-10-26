#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Represents the change in the price of an option from the closing price of one day to the closing price on the next day on which the option is traded.
struct NetChange {

    static constexpr const char* name = "Net Change";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr NetChange()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NetChange(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NetChange field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
