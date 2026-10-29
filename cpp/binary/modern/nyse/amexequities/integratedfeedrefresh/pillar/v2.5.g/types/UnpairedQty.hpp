#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

// The number of unpaired shares priced at or better than the Reference Price.
struct UnpairedQty {

    static constexpr const char* name = "Unpaired Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnpairedQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnpairedQty(const std::uint32_t value)
     : value{ value } {}

    // get value of UnpairedQty field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
