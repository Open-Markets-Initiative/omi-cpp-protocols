#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Set to the book center price while the Itayose method is in place or while a quote is displayed
struct BookCenterPrice {

    static constexpr const char* name = "Book Center Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr BookCenterPrice()
     : value{ 0 } {}

    // constructor for BookCenterPrice field
    constexpr explicit BookCenterPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BookCenterPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BookCenterPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
