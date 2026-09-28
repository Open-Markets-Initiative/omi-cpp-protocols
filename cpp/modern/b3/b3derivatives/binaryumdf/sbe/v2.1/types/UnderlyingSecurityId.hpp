#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// Underlying instrument's security ID.
struct UnderlyingSecurityId {

    static constexpr const char* name = "Underlying Security Id";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr UnderlyingSecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSecurityId(const std::uint64_t value)
     : value{ value } {}

    // get value of UnderlyingSecurityId field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
