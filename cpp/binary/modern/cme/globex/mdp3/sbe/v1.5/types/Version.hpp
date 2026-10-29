#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {

// 
struct Version {

    static constexpr const char* name = "Version";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static constexpr std::array<type, 2> static_values{ 5, 0 };

    // default constructor
    constexpr Version()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Version(const std::uint16_t value)
     : value{ value } {}

    // get value of Version field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
