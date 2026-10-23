#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Start date of a broken date period
struct BrokenDateStart {

    static constexpr const char* name = "Broken Date Start";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr BrokenDateStart()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BrokenDateStart(const std::uint16_t value)
     : value{ value } {}

    // get value of BrokenDateStart field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
