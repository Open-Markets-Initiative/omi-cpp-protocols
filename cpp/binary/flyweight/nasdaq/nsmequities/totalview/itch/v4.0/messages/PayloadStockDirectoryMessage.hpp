#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketCategory.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/RoundLotsOnly.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Market data redistributors should process this message to populate the Financial Status
// Indicator (required display field) and the Market Category (recommended display field) for
// NASDAQ-listed issues.
class PayloadStockDirectoryMessage {
  public:
    static constexpr const char* name = "PayloadStockDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadStockDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadStockDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::string_view stock() const { return view::text(at(4), 6, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(10))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(11))); }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(12)); }

    RoundLotsOnly round_lots_only() const { return static_cast<RoundLotsOnly>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "PayloadStockDirectoryMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", market_category=";
        out << market_category();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", round_lots_only=";
        out << round_lots_only();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadStockDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
