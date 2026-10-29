#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// sessionVerID
struct SessionVerId {

    static constexpr const char* name = "Session Ver Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SessionVerId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionVerId(const std::uint64_t value)
     : value{ value } {}

    // get value of SessionVerId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
