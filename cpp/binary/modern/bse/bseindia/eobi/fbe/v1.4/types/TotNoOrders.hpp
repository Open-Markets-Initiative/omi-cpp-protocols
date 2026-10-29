#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Corresponding number of orders for this instrument.
struct TotNoOrders {

    static constexpr const char* name = "Tot No Orders";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotNoOrders()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNoOrders(const std::uint32_t value)
     : value{ value } {}

    // get value of TotNoOrders field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
