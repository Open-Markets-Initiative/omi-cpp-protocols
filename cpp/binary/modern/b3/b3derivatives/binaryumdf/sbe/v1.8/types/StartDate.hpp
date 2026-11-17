// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8: types/StartDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// startDate
struct StartDate {

    static constexpr const char* name = "Start Date";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr StartDate()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit StartDate(const std::int32_t value)
     : value{ value } {}

    // get value of StartDate field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
