#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The Ask price. Use the Price scale from the Series Index message.
struct AskPrice {

    static constexpr const char* name = "Ask Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr AskPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskPrice(const std::int32_t value)
     : value{ value } {}

    // get value of AskPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
