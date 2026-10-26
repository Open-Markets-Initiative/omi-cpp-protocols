#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// Leg's security ID.
struct LegSecurityId {

    static constexpr const char* name = "Leg Security Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr LegSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegSecurityId(const std::uint64_t value)
     : value{ value } {}

    // get value of LegSecurityId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
