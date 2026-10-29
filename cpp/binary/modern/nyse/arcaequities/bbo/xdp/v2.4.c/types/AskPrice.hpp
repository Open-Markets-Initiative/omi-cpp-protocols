#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// The Ask price. Use the Price scale from the Symbol Index message.
struct AskPrice {

    static constexpr const char* name = "Ask Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of AskPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
