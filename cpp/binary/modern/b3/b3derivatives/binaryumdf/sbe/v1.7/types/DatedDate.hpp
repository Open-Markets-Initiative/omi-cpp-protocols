#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// datedDate
struct DatedDate {

    static constexpr const char* name = "Dated Date";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr DatedDate()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit DatedDate(const std::int32_t value)
     : value{ value } {}

    // get value of DatedDate field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
