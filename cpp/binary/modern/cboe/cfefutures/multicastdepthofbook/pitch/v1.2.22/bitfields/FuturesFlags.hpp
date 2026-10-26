#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Futures Flags bitfields
struct FuturesFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Futures Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Variance = 0x01;
    };

    // default constructor
    constexpr FuturesFlags()
     : value{ 0 } {}

    // Set for a Variance Future, clear for a Standard Future
    [[nodiscard]] constexpr bool Variance() const {
        return value & mask::Variance;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
