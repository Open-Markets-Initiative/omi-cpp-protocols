#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Not Applicable to LSE.
struct AverageDailyTurnoverAdt {

    static constexpr const char* name = "Average Daily Turnover Adt";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr AverageDailyTurnoverAdt()
     : value{ 0 } {}

    // constructor for AverageDailyTurnoverAdt field
    constexpr explicit AverageDailyTurnoverAdt(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AverageDailyTurnoverAdt field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AverageDailyTurnoverAdt field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
