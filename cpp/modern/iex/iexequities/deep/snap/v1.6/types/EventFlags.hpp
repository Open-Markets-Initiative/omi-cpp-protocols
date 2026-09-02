#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::snap::v1_6 {


// Identifies event processing by the System
struct EventFlags {

    static constexpr auto name = "Event Flags";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr EventFlags()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventFlags(const std::uint8_t &value)
     : value{ value } {}

    // get value of EventFlags field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
