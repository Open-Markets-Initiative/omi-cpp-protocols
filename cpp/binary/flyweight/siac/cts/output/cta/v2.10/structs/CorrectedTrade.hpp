#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SaleConditions.hpp"
#include "../common/Decimal.hpp"
#include "../enums/StopStockIndicator.hpp"
#include "../enums/TradeThroughExemptIndicator.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

// Corrected Trade
class CorrectedTrade {
  public:
    static constexpr const char* name = "CorrectedTrade";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CorrectedTrade(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CorrectedTrade has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    SaleConditions sale_conditions() const { return SaleConditions{ bytes_.subspan(0) }; }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(4))), -6); }

    std::uint32_t trade_volume() const { return wire::read_u32_be(at(12)); }

    std::uint8_t sellers_sale_days() const { return wire::read_u8(at(16)); }

    StopStockIndicator stop_stock_indicator() const { return static_cast<StopStockIndicator>(wire::read_char(at(17))); }

    TradeThroughExemptIndicator trade_through_exempt_indicator() const { return static_cast<TradeThroughExemptIndicator>(wire::read_char(at(18))); }

    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const { return static_cast<ShortSaleRestrictionIndicator>(wire::read_char(at(19))); }

    void print(std::ostream& out) const {
        out << "CorrectedTrade{";
        out << "sale_conditions=";
        sale_conditions().print(out);
        out << ", trade_price=";
        out << trade_price();
        out << ", trade_volume=";
        out << trade_volume();
        out << ", sellers_sale_days=";
        out << static_cast<int>(sellers_sale_days());
        out << ", stop_stock_indicator=";
        out << stop_stock_indicator();
        out << ", trade_through_exempt_indicator=";
        out << trade_through_exempt_indicator();
        out << ", short_sale_restriction_indicator=";
        out << short_sale_restriction_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CorrectedTrade& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
