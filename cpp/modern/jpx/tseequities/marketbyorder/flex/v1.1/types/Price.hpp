#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Price registered on the order book; for market orders set to the maximum 64-bit value
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // constructor for Price field
    constexpr explicit Price(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Price field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // does Price hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of Price field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
