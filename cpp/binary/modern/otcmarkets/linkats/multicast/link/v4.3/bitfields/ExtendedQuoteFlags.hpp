// OtcMarkets.LinkAts.Multicast.Link.v4.3: bitfields/ExtendedQuoteFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Extended Quote Information
struct ExtendedQuoteFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Extended Quote Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type QuoteSaturated = 0x01;
        static const type BidAutoEx = 0x02;
        static const type OfferAutoEx = 0x04;
        static const type NmsConditionalQuote = 0x08;
    };

    // default constructor
    constexpr ExtendedQuoteFlags()
     : value{ 0 } {}

    // Quote should be considered for inside price
    [[nodiscard]] constexpr bool QuoteSaturated() const {
        return value & mask::QuoteSaturated;
    }

    // Bid Auto Execution enabled
    [[nodiscard]] constexpr bool BidAutoEx() const {
        return value & mask::BidAutoEx;
    }

    // Offer Auto Execution enabled
    [[nodiscard]] constexpr bool OfferAutoEx() const {
        return value & mask::OfferAutoEx;
    }

    // Displayed quote size is a round lot at least two times greater than the minimum round lot size and cannot be partially filled.
    [[nodiscard]] constexpr bool NmsConditionalQuote() const {
        return value & mask::NmsConditionalQuote;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
