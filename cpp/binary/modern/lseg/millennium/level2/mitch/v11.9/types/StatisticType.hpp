#pragma once

#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Statistic Type
struct StatisticType {

    static constexpr auto name = "Statistic Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr StatisticType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatisticType(const char &value)
     : value{ value } {}

    // get value of StatisticType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
