#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// The start time of query range in UNIX epoch nanoseconds
struct Start {

    static constexpr auto name = "Start";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr Start()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Start(const std::uint64_t &value)
     : value{ value } {}

    // get value of Start field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
