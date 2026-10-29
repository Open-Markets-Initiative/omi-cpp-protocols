#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

// The order price. Use the Price scale from the symbol-mapping index.
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Price(const std::int32_t value)
     : value{ value } {}

    // get value of Price field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
