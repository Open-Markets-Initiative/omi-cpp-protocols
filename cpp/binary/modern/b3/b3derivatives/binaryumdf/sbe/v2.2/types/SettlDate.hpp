// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: types/SettlDate.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// settlDate
struct SettlDate {

    static constexpr const char* name = "Settl Date";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr SettlDate()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit SettlDate(const std::int32_t value)
     : value{ value } {}

    // get value of SettlDate field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
