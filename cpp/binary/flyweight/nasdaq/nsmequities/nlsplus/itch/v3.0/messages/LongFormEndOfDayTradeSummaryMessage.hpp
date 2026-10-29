#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketCategory.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// End of Day Trade Summary carrying eight byte prices.
class LongFormEndOfDayTradeSummaryMessage {
  public:
    static constexpr const char* name = "LongFormEndOfDayTradeSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongFormEndOfDayTradeSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongFormEndOfDayTradeSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 49;
    static constexpr std::size_t fixed_size = 49;
    std::size_t encoded_size() const { return 49; }

    std::string_view issue_symbol() const { return view::text(at(0), 8, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(8))); }

    Decimal consolidated_high_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(9))), -4); }

    Decimal consolidated_low_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(17))), -4); }

    Decimal consolidated_closing_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(25))), -4); }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(33)); }

    Decimal consolidated_open_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(41))), -4); }

    void print(std::ostream& out) const {
        out << "LongFormEndOfDayTradeSummaryMessage{";
        out << "issue_symbol=";
        print::text(out, issue_symbol());
        out << ", market_category=";
        out << market_category();
        out << ", consolidated_high_price_long=";
        out << consolidated_high_price_long();
        out << ", consolidated_low_price_long=";
        out << consolidated_low_price_long();
        out << ", consolidated_closing_price_long=";
        out << consolidated_closing_price_long();
        out << ", consolidated_volume=";
        out << consolidated_volume();
        out << ", consolidated_open_price_long=";
        out << consolidated_open_price_long();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongFormEndOfDayTradeSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
