#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Best bid at the time the execution processing finishes; set to 0 at market close
struct BestBid {

    static constexpr const char* name = "Best Bid";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr BestBid()
     : value{ 0 } {}

    // constructor for BestBid field
    constexpr explicit BestBid(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestBid field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BestBid field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
