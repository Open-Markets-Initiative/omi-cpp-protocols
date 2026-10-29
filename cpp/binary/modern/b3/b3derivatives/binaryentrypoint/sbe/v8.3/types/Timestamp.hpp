#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// timestamp
struct Timestamp {

    static constexpr auto name = "Timestamp";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr Timestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Timestamp(const std::uint64_t &value)
     : value{ value } {}

    // get value of Timestamp field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
