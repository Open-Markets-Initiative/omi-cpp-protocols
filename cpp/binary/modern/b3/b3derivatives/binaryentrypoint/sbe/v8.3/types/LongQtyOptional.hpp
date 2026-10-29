#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// Long Quantity.
struct LongQtyOptional {

    static constexpr const char* name = "Long Qty Optional";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr LongQtyOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LongQtyOptional(const std::uint64_t value)
     : value{ value } {}

    // get value of LongQtyOptional field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
