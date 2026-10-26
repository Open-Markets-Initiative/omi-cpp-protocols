#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/BidCondition.hpp"
#include "../enums/OfferCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the message format that will be used in the real-time feed and refresh service to
// disseminate both sides of the MIAX Simple Top of Market for options with low premiums and
// small aggregate MIAX Best Bid or Offer (MBBO) size.
class SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage {
  public:
    static constexpr const char* name = "SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t product_id() const { return wire::read_u32_le(at(4)); }

    Decimal bid_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_le(at(8))), -2); }

    std::uint16_t bid_size_short() const { return wire::read_u16_le(at(10)); }

    std::uint16_t bid_priority_customer_size_short() const { return wire::read_u16_le(at(12)); }

    BidCondition bid_condition() const { return static_cast<BidCondition>(wire::read_char(at(14))); }

    Decimal offer_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_le(at(15))), -2); }

    std::uint16_t offer_size_short() const { return wire::read_u16_le(at(17)); }

    std::uint16_t offer_priority_customer_size_short() const { return wire::read_u16_le(at(19)); }

    OfferCondition offer_condition() const { return static_cast<OfferCondition>(wire::read_char(at(21))); }

    void print(std::ostream& out) const {
        out << "SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", product_id=";
        out << product_id();
        out << ", bid_price_short=";
        out << bid_price_short();
        out << ", bid_size_short=";
        out << bid_size_short();
        out << ", bid_priority_customer_size_short=";
        out << bid_priority_customer_size_short();
        out << ", bid_condition=";
        out << bid_condition();
        out << ", offer_price_short=";
        out << offer_price_short();
        out << ", offer_size_short=";
        out << offer_size_short();
        out << ", offer_priority_customer_size_short=";
        out << offer_priority_customer_size_short();
        out << ", offer_condition=";
        out << offer_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
