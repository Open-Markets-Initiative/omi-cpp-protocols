#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// longQty
struct LongQty {

    static constexpr const char* name = "Long Qty";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr LongQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LongQty(const std::uint64_t value)
     : value{ value } {}

    // get value of LongQty field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
