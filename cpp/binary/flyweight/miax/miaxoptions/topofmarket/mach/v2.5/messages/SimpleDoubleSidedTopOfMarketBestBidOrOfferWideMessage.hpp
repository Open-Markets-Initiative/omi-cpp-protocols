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
// disseminate both sides of the MIAX Simple Top of Market for options with high premiums or
// large aggregate MIAX Best Bid or Offer (MBBO) sizes.
class SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage {
  public:
    static constexpr const char* name = "SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t product_id() const { return wire::read_u32_le(at(4)); }

    Decimal bid_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(8))), -4); }

    std::uint32_t bid_size_long() const { return wire::read_u32_le(at(12)); }

    std::uint32_t bid_priority_customer_size_long() const { return wire::read_u32_le(at(16)); }

    BidCondition bid_condition() const { return static_cast<BidCondition>(wire::read_char(at(20))); }

    Decimal offer_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(21))), -4); }

    std::uint32_t offer_size_long() const { return wire::read_u32_le(at(25)); }

    std::uint32_t offer_priority_customer_size_long() const { return wire::read_u32_le(at(29)); }

    OfferCondition offer_condition() const { return static_cast<OfferCondition>(wire::read_char(at(33))); }

    void print(std::ostream& out) const {
        out << "SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", product_id=";
        out << product_id();
        out << ", bid_price_long=";
        out << bid_price_long();
        out << ", bid_size_long=";
        out << bid_size_long();
        out << ", bid_priority_customer_size_long=";
        out << bid_priority_customer_size_long();
        out << ", bid_condition=";
        out << bid_condition();
        out << ", offer_price_long=";
        out << offer_price_long();
        out << ", offer_size_long=";
        out << offer_size_long();
        out << ", offer_priority_customer_size_long=";
        out << offer_priority_customer_size_long();
        out << ", offer_condition=";
        out << offer_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
