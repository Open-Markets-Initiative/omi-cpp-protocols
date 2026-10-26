#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Reserved for future use
struct StatisticsReserved {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Statistics Reserved";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Unused8 = 0xFF;
    };

    // default constructor
    constexpr StatisticsReserved()
     : value{ 0 } {}

    // Unused
    [[nodiscard]] constexpr bool Unused8() const {
        return value & mask::Unused8;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
