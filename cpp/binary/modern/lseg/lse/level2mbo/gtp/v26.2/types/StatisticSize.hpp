#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// The value of size type statistics.
struct StatisticSize {

    static constexpr const char* name = "Statistic Size";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::uint64_t;

    // default constructor
    constexpr StatisticSize()
     : value{ 0 } {}

    // constructor for StatisticSize field
    constexpr explicit StatisticSize(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of StatisticSize field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of StatisticSize field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
