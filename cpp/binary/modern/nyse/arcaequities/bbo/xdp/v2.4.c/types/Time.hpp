#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// Format : HHMMSSmmm (mmm = milliseconds)
struct Time {

    static constexpr const char* name = "Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr Time()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Time(const std::uint32_t value)
     : value{ value } {}

    // get value of Time field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
