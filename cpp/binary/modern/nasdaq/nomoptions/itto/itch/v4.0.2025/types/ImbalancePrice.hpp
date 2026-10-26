#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The imbalance price. 0 for Price Improvement (PRISM) Auction
struct ImbalancePrice {

    static constexpr const char* name = "Imbalance Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ImbalancePrice()
     : value{ 0 } {}

    // constructor for ImbalancePrice field
    constexpr explicit ImbalancePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ImbalancePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ImbalancePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
