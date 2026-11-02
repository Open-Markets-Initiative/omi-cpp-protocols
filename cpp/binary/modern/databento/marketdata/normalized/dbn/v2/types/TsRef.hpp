#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The reference timestamp of the statistic value expressed as the number of nanoseconds since the UNIX epoch
struct TsRef {

    static constexpr auto name = "Ts Ref";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr TsRef()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TsRef(const std::uint64_t &value)
     : value{ value } {}

    // get value of TsRef field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
