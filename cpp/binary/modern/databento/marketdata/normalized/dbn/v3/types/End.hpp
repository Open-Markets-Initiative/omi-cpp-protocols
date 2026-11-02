#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The end time of query range in UNIX epoch nanoseconds; no value when unbounded
struct End {

    static constexpr auto name = "End";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 18446744073709551615ULL;

    // default constructor
    constexpr End()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit End(const std::uint64_t &value)
     : value{ value } {}

    // get value of End field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
