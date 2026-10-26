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
#include "../enums/MbboCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the message format that will be used to disseminate each side of the MIAX Simple Top
// of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO)
// size. "O" = Simple Top of Market on Offer side.
class SimpleTopOfMarketBestBidOrOfferCompactOfferMessage {
  public:
    static constexpr const char* name = "SimpleTopOfMarketBestBidOrOfferCompactOfferMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleTopOfMarketBestBidOrOfferCompactOfferMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleTopOfMarketBestBidOrOfferCompactOfferMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    static constexpr std::size_t fixed_size = 15;
    std::size_t encoded_size() const { return 15; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t product_id() const { return wire::read_u32_le(at(4)); }

    Decimal mbbo_price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_le(at(8))), -2); }

    std::uint16_t mbbo_size_short() const { return wire::read_u16_le(at(10)); }

    std::uint16_t mbbo_priority_customer_size_short() const { return wire::read_u16_le(at(12)); }

    MbboCondition mbbo_condition() const { return static_cast<MbboCondition>(wire::read_char(at(14))); }

    void print(std::ostream& out) const {
        out << "SimpleTopOfMarketBestBidOrOfferCompactOfferMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", product_id=";
        out << product_id();
        out << ", mbbo_price_short=";
        out << mbbo_price_short();
        out << ", mbbo_size_short=";
        out << mbbo_size_short();
        out << ", mbbo_priority_customer_size_short=";
        out << mbbo_priority_customer_size_short();
        out << ", mbbo_condition=";
        out << mbbo_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleTopOfMarketBestBidOrOfferCompactOfferMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
