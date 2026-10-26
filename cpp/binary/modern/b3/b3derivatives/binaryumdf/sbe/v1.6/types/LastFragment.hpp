#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// lastFragment
struct LastFragment {

    static constexpr auto name = "Last Fragment";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr LastFragment()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastFragment(const std::uint8_t &value)
     : value{ value } {}

    // get value of LastFragment field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
