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

// Summarises the consolidated trading activity for an issue at the end of the trading day.
class EndOfDayTradeSummaryMessage {
  public:
    static constexpr const char* name = "EndOfDayTradeSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfDayTradeSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfDayTradeSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 33;
    static constexpr std::size_t fixed_size = 33;
    std::size_t encoded_size() const { return 33; }

    std::string_view issue_symbol() const { return view::text(at(0), 8, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(8))); }

    Decimal consolidated_high_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(9))), -4); }

    Decimal consolidated_low_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(13))), -4); }

    Decimal consolidated_closing_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(17))), -4); }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(21)); }

    Decimal consolidated_open_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(29))), -4); }

    void print(std::ostream& out) const {
        out << "EndOfDayTradeSummaryMessage{";
        out << "issue_symbol=";
        print::text(out, issue_symbol());
        out << ", market_category=";
        out << market_category();
        out << ", consolidated_high_price=";
        out << consolidated_high_price();
        out << ", consolidated_low_price=";
        out << consolidated_low_price();
        out << ", consolidated_closing_price=";
        out << consolidated_closing_price();
        out << ", consolidated_volume=";
        out << consolidated_volume();
        out << ", consolidated_open_price=";
        out << consolidated_open_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfDayTradeSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
