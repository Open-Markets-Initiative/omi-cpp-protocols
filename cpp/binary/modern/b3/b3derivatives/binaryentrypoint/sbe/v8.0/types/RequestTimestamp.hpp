#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// requestTimestamp
struct RequestTimestamp {

    static constexpr auto name = "Request Timestamp";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr RequestTimestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RequestTimestamp(const std::uint64_t &value)
     : value{ value } {}

    // get value of RequestTimestamp field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
