#pragma once

#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Additional order attributes
struct OrderAttributes {

    // underlying type
    using type = std::uint16_t;

    static constexpr const char* name = "Order Attributes";
    static constexpr std::size_t size = 2;

    struct mask {
        static const type Force = 0x0001;
        static const type ShortSell = 0x0002;
        static const type MarketBid = 0x0004;
        static const type PriceStabilization = 0x0008;
        static const type OverrideCrossing = 0x0010;
        static const type Undisclosed = 0x0020;
    };

    // default constructor
    constexpr OrderAttributes()
     : value{ 0 } {}

    // Force
    [[nodiscard]] constexpr bool Force() const {
        return value & mask::Force;
    }

    // Short Sell
    [[nodiscard]] constexpr bool ShortSell() const {
        return value & mask::ShortSell;
    }

    // Market Bid
    [[nodiscard]] constexpr bool MarketBid() const {
        return value & mask::MarketBid;
    }

    // Price Stabilization
    [[nodiscard]] constexpr bool PriceStabilization() const {
        return value & mask::PriceStabilization;
    }

    // Override Crossing
    [[nodiscard]] constexpr bool OverrideCrossing() const {
        return value & mask::OverrideCrossing;
    }

    // Undisclosed
    [[nodiscard]] constexpr bool Undisclosed() const {
        return value & mask::Undisclosed;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
