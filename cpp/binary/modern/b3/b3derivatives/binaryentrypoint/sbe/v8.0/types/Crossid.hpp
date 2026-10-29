#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// crossID
struct Crossid {

    static constexpr const char* name = "CrossId";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Crossid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Crossid(const std::uint64_t value)
     : value{ value } {}

    // get value of Crossid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
