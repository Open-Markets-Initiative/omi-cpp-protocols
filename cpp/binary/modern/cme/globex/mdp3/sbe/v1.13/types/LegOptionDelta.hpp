#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Delta used to calculate the quantity of futures used to cover the option or option strategy
struct LegOptionDelta {

    static constexpr const char* name = "Leg Option Delta";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr LegOptionDelta()
     : value{ 0 } {}

    // constructor for LegOptionDelta field
    constexpr explicit LegOptionDelta(const std::int32_t value)
     : value{ value } {}

    // get underlying integer of LegOptionDelta field
    [[nodiscard]] std::int32_t integer() const {
        return value;
    }

    // decimal value of LegOptionDelta field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
