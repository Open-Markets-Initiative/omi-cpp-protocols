#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// stopPx
struct StopPx {

    static constexpr const char* name = "Stop Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr StopPx()
     : value{ 0 } {}

    // constructor for StopPx field
    constexpr explicit StopPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of StopPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of StopPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
