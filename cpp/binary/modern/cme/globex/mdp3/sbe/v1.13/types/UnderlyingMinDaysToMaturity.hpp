// Cme.Globex.Mdp3.Sbe.v1.13: types/UnderlyingMinDaysToMaturity.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Minimum days to maturity remaining of the underlying instruments to qualify for GC basket. Will contain null value for Repo specials
struct UnderlyingMinDaysToMaturity {

    static constexpr const char* name = "Underlying Min Days To Maturity";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor: the null the model states, where it states one
    constexpr UnderlyingMinDaysToMaturity()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit UnderlyingMinDaysToMaturity(const std::uint16_t value)
     : value{ value } {}

    // get value of UnderlyingMinDaysToMaturity field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
