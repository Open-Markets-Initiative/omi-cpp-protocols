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

// This is the message format that will be used to disseminate each side of the MIAX Top of
// Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size
class CompactComplexTopOfMarketOfferMessage {
  public:
    static constexpr const char* name = "CompactComplexTopOfMarketOfferMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CompactComplexTopOfMarketOfferMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CompactComplexTopOfMarketOfferMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    static constexpr std::size_t fixed_size = 15;
    std::size_t encoded_size() const { return 15; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(4)); }

    Decimal compact_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i16_le(at(8))), -2); }

    std::uint16_t compact_size() const { return wire::read_u16_le(at(10)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(12).template first<2>(); }

    TopOfMarketQuoteCondition top_of_market_quote_condition() const { return static_cast<TopOfMarketQuoteCondition>(wire::read_char(at(14))); }

    void print(std::ostream& out) const {
        out << "CompactComplexTopOfMarketOfferMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", compact_price=";
        out << compact_price();
        out << ", compact_size=";
        out << compact_size();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << ", top_of_market_quote_condition=";
        out << top_of_market_quote_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CompactComplexTopOfMarketOfferMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
