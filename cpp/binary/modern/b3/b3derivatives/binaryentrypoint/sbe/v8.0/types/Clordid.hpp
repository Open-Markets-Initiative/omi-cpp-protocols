#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// clOrdID
struct Clordid {

    static constexpr const char* name = "ClOrdId";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Clordid()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Clordid(const std::uint64_t value)
     : value{ value } {}

    // get value of Clordid field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
