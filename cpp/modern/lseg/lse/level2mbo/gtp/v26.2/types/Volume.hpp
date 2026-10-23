#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Cumulative volume of all trades for the trading day.
struct Volume {

    static constexpr const char* name = "Volume";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr Volume()
     : value{ 0 } {}

    // constructor for Volume field
    constexpr explicit Volume(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of Volume field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of Volume field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
