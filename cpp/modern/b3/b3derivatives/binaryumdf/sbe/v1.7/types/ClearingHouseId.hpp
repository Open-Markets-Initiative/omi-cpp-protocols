#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// clearingHouseID
struct ClearingHouseId {

    static constexpr const char* name = "Clearing House Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr ClearingHouseId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClearingHouseId(const std::uint64_t value)
     : value{ value } {}

    // get value of ClearingHouseId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
