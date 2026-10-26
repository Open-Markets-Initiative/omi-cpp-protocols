#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Quantity at equilibrium price on the ask side
struct AvailableAskQuantityAtEquilibriumPrice {

    static constexpr const char* name = "Available Ask Quantity At Equilibrium Price";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AvailableAskQuantityAtEquilibriumPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AvailableAskQuantityAtEquilibriumPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of AvailableAskQuantityAtEquilibriumPrice field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
