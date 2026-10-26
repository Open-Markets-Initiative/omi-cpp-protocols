#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// This field specifies the security Unit of Trade in shares. Valid values are 1, 10, 50 and 100
struct UnitOfTrade {

    static constexpr const char* name = "Unit Of Trade";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr UnitOfTrade()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnitOfTrade(const std::uint16_t value)
     : value{ value } {}

    // get value of UnitOfTrade field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
