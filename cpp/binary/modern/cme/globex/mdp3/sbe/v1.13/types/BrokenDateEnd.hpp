#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// End date of a broken date period
struct BrokenDateEnd {

    static constexpr const char* name = "Broken Date End";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr BrokenDateEnd()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BrokenDateEnd(const std::uint16_t value)
     : value{ value } {}

    // get value of BrokenDateEnd field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
