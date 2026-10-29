#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// individualAllocID
struct IndividualAllocId {

    static constexpr const char* name = "Individual Alloc Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr IndividualAllocId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndividualAllocId(const std::uint64_t value)
     : value{ value } {}

    // get value of IndividualAllocId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
