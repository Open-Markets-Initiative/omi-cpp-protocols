#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Qty Executed - 6 implied decimals
struct Shares {

    static constexpr const char* name = "Shares";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Shares()
     : value{ 0 } {}

    // constructor for Shares field
    constexpr explicit Shares(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of Shares field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of Shares field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
