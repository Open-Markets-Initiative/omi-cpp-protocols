#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// In Book entry - aggregate number of orders at given price level
struct NumberOfOrdersOptional {

    static constexpr const char* name = "Number Of Orders Optional";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr NumberOfOrdersOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfOrdersOptional(const std::int32_t value)
     : value{ value } {}

    // get value of NumberOfOrdersOptional field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
