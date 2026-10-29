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

// Summarises the consolidated trading activity for a NextShares issue, each price paired with
// the Nav offset to apply to it.
class NextSharesEndOfDayTradeSummaryMessage {
  public:
    static constexpr const char* name = "NextSharesEndOfDayTradeSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NextSharesEndOfDayTradeSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NextSharesEndOfDayTradeSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 49;
    static constexpr std::size_t fixed_size = 49;
    std::size_t encoded_size() const { return 49; }

    std::string_view issue_symbol() const { return view::text(at(0), 8, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(8))); }

    Decimal consolidated_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(9))), -4); }

    Decimal nav_offset_amount_high() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(13))), -4); }

    Decimal consolidated_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(17))), -4); }

    Decimal nav_offset_amount_low() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(21))), -4); }

    Decimal consolidated_closing_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(25))), -4); }

    Decimal nav_offset_amount_closing() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(29))), -4); }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(33)); }

    Decimal consolidated_open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(41))), -4); }

    Decimal nav_offset_amount_open() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(45))), -4); }

    void print(std::ostream& out) const {
        out << "NextSharesEndOfDayTradeSummaryMessage{";
        out << "issue_symbol=";
        print::text(out, issue_symbol());
        out << ", market_category=";
        out << market_category();
        out << ", consolidated_high_price=";
        out << consolidated_high_price();
        out << ", nav_offset_amount_high=";
        out << nav_offset_amount_high();
        out << ", consolidated_low_price=";
        out << consolidated_low_price();
        out << ", nav_offset_amount_low=";
        out << nav_offset_amount_low();
        out << ", consolidated_closing_price=";
        out << consolidated_closing_price();
        out << ", nav_offset_amount_closing=";
        out << nav_offset_amount_closing();
        out << ", consolidated_volume=";
        out << consolidated_volume();
        out << ", consolidated_open_price=";
        out << consolidated_open_price();
        out << ", nav_offset_amount_open=";
        out << nav_offset_amount_open();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NextSharesEndOfDayTradeSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
