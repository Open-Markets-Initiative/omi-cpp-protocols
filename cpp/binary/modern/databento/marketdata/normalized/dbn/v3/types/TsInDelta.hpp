#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The matching-engine-sending timestamp expressed as the number of nanoseconds before ts_recv
struct TsInDelta {

    static constexpr const char* name = "Ts In Delta";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr TsInDelta()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TsInDelta(const std::int32_t value)
     : value{ value } {}

    // get value of TsInDelta field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
