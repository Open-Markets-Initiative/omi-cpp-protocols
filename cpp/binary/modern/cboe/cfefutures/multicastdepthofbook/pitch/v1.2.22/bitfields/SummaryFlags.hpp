#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Summary Flags bitfields
struct SummaryFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Summary Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type HighPriceValid = 0x01;
        static const type HighPriceIsBid = 0x02;
        static const type LowPriceValid = 0x04;
        static const type LowPriceIsOffer = 0x08;
        static const type OpenCloseValid = 0x10;
    };

    // default constructor
    constexpr SummaryFlags()
     : value{ 0 } {}

    // Set if High Price is a valid value
    [[nodiscard]] constexpr bool HighPriceValid() const {
        return value & mask::HighPriceValid;
    }

    // Set if High Price was set by the highest bid (rather than a trade)
    [[nodiscard]] constexpr bool HighPriceIsBid() const {
        return value & mask::HighPriceIsBid;
    }

    // Set if Low Price is a valid value
    [[nodiscard]] constexpr bool LowPriceValid() const {
        return value & mask::LowPriceValid;
    }

    // Set if Low Price was set by the lowest offer (rather than a trade)
    [[nodiscard]] constexpr bool LowPriceIsOffer() const {
        return value & mask::LowPriceIsOffer;
    }

    // Set if both Open Price and Close Price fields contain valid values
    [[nodiscard]] constexpr bool OpenCloseValid() const {
        return value & mask::OpenCloseValid;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
