// OtcMarkets.LinkAts.Multicast.Link.v4.3: bitfields/QuoteFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Quote Information
struct QuoteFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Quote Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type UpdateSide = 0x01;
        static const type State = 0x02;
        static const type AskUnsolicited = 0x04;
        static const type AskPriced = 0x08;
        static const type AskBidWanted = 0x10;
        static const type BidUnsolicited = 0x20;
        static const type BidPriced = 0x40;
        static const type BidAskWanted = 0x80;
    };

    // default constructor
    constexpr QuoteFlags()
     : value{ 0 } {}

    // Ask or Bid
    [[nodiscard]] constexpr bool UpdateSide() const {
        return value & mask::UpdateSide;
    }

    // Open or Closed
    [[nodiscard]] constexpr bool State() const {
        return value & mask::State;
    }

    // Ask Unsolicited
    [[nodiscard]] constexpr bool AskUnsolicited() const {
        return value & mask::AskUnsolicited;
    }

    // Ask Priced
    [[nodiscard]] constexpr bool AskPriced() const {
        return value & mask::AskPriced;
    }

    // Ask Bid Wanted
    [[nodiscard]] constexpr bool AskBidWanted() const {
        return value & mask::AskBidWanted;
    }

    // Bid Unsolicited
    [[nodiscard]] constexpr bool BidUnsolicited() const {
        return value & mask::BidUnsolicited;
    }

    // Bid Priced
    [[nodiscard]] constexpr bool BidPriced() const {
        return value & mask::BidPriced;
    }

    // Bid Ask Wanted
    [[nodiscard]] constexpr bool BidAskWanted() const {
        return value & mask::BidAskWanted;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
