#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// custodyAllocationType
struct CustodyAllocationType {

    static constexpr const char* name = "Custody Allocation Type";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CustodyAllocationType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CustodyAllocationType(const std::uint32_t value)
     : value{ value } {}

    // get value of CustodyAllocationType field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
