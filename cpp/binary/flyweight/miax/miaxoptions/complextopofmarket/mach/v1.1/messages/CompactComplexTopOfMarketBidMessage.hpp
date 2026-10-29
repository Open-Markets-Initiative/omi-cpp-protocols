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
#include "../enums/TopOfMarketQuoteCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This is the message format that will be used to disseminate each side of the MIAX Complex
// Top of Market for options with low Net Price and small aggregate MIAX Best Bid or Offer
// (MBBO) size
class CompactComplexTopOfMarketBidMessage {
  public:
    static constexpr const char* name = "CompactComplexTopOfMarketBidMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CompactComplexTopOfMarketBidMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CompactComplexTopOfMarketBidMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    Decimal compact_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i16_le(at(8))), -2); }

    std::uint16_t compact_size() const { return wire::read_u16_le(at(10)); }

    TopOfMarketQuoteCondition top_of_market_quote_condition() const { return static_cast<TopOfMarketQuoteCondition>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "CompactComplexTopOfMarketBidMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", compact_price=";
        out << compact_price();
        out << ", compact_size=";
        out << compact_size();
        out << ", top_of_market_quote_condition=";
        out << top_of_market_quote_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CompactComplexTopOfMarketBidMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
