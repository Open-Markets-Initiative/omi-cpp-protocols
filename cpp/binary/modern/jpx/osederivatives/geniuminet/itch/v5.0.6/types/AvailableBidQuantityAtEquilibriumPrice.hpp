#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Quantity at equilibrium price on the bid side
struct AvailableBidQuantityAtEquilibriumPrice {

    static constexpr const char* name = "Available Bid Quantity At Equilibrium Price";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AvailableBidQuantityAtEquilibriumPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AvailableBidQuantityAtEquilibriumPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of AvailableBidQuantityAtEquilibriumPrice field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
