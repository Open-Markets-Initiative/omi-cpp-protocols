#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Sequence per Stream Id of the Business message
struct Sequence1 {

    static constexpr const char* name = "Sequence 1";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Sequence1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Sequence1(const std::uint32_t value)
     : value{ value } {}

    // get value of Sequence1 field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
