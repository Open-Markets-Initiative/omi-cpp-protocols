#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// allocID
struct AllocId {

    static constexpr const char* name = "Alloc Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AllocId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AllocId(const std::uint64_t value)
     : value{ value } {}

    // get value of AllocId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
