#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// cumQty
struct CumQty {

    static constexpr const char* name = "Cum Qty";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CumQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CumQty(const std::uint64_t value)
     : value{ value } {}

    // get value of CumQty field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
