#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// The start of the mapping interval expressed as the number of nanoseconds since the UNIX epoch
struct StartTs {

    static constexpr auto name = "Start Ts";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr StartTs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StartTs(const std::uint64_t &value)
     : value{ value } {}

    // get value of StartTs field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
