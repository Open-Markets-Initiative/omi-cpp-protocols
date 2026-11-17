// Cme.Globex.Mdp3.Sbe.v1.13: types/MaturityDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Maturity Date
struct MaturityDate {

    static constexpr const char* name = "Maturity Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor: the null the model states, where it states one
    constexpr MaturityDate()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MaturityDate(const std::uint16_t value)
     : value{ value } {}

    // get value of MaturityDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
