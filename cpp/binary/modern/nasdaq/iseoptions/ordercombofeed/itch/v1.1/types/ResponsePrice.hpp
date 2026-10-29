#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Price of the auction response in fixed point format with 6 whole number places followed by 4 decimal digits. The response, if shown (zero if not shown) is the best response on the contra side.
struct ResponsePrice {

    static constexpr const char* name = "Response Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr ResponsePrice()
     : value{ 0 } {}

    // constructor for ResponsePrice field
    constexpr explicit ResponsePrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ResponsePrice field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ResponsePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
