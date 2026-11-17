// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/ExerciseStyle.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct ExerciseStyle {

    static constexpr auto name = "Exercise Style";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExerciseStyle()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExerciseStyle(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExerciseStyle field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
