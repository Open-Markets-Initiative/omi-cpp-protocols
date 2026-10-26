#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// The statistic that is disseminated with this message instance.
struct StatisticType {

    static constexpr const char* name = "Statistic Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StatisticType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatisticType(const std::uint16_t value)
     : value{ value } {}

    // get value of StatisticType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
