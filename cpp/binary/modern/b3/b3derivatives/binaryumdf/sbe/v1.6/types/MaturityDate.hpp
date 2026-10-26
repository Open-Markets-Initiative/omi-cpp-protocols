#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// maturityDate
struct MaturityDate {

    static constexpr const char* name = "Maturity Date";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0;

    // default constructor
    constexpr MaturityDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityDate(const std::int32_t value)
     : value{ value } {}

    // get value of MaturityDate field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
