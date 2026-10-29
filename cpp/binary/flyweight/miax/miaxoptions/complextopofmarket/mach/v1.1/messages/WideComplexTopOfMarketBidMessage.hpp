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

// This is the message format that will be used to disseminate MIAX Complex Top of Market for
// strategies with high net price or large aggregate MIAX Best Bid or Offer (MBBO) size.
class WideComplexTopOfMarketBidMessage {
  public:
    static constexpr const char* name = "WideComplexTopOfMarketBidMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit WideComplexTopOfMarketBidMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every WideComplexTopOfMarketBidMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    Decimal wide_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(8))), -4); }

    std::uint32_t wide_size() const { return wire::read_u32_le(at(16)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(20).template first<4>(); }

    TopOfMarketQuoteCondition top_of_market_quote_condition() const { return static_cast<TopOfMarketQuoteCondition>(wire::read_char(at(24))); }

    void print(std::ostream& out) const {
        out << "WideComplexTopOfMarketBidMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", wide_price=";
        out << wide_price();
        out << ", wide_size=";
        out << wide_size();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", top_of_market_quote_condition=";
        out << top_of_market_quote_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const WideComplexTopOfMarketBidMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
