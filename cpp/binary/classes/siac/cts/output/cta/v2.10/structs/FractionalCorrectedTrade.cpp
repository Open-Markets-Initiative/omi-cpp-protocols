#include "FractionalCorrectedTrade.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

FractionalCorrectedTrade::FractionalCorrectedTrade(const SaleConditions& sale_conditions, Decimal trade_price, Decimal fractional_trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator)
  : sale_conditions_(sale_conditions), trade_price_(trade_price), fractional_trade_volume_(fractional_trade_volume), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), short_sale_restriction_indicator_(short_sale_restriction_indicator) {}

const SaleConditions& FractionalCorrectedTrade::sale_conditions() const { return sale_conditions_; }
SaleConditions& FractionalCorrectedTrade::sale_conditions() { return sale_conditions_; }
void FractionalCorrectedTrade::set_sale_conditions(const SaleConditions& value) { sale_conditions_ = value; }

Decimal FractionalCorrectedTrade::trade_price() const { return trade_price_; }
void FractionalCorrectedTrade::set_trade_price(Decimal value) { trade_price_ = value; }

Decimal FractionalCorrectedTrade::fractional_trade_volume() const { return fractional_trade_volume_; }
void FractionalCorrectedTrade::set_fractional_trade_volume(Decimal value) { fractional_trade_volume_ = value; }

std::uint8_t FractionalCorrectedTrade::sellers_sale_days() const { return sellers_sale_days_; }
void FractionalCorrectedTrade::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator FractionalCorrectedTrade::stop_stock_indicator() const { return stop_stock_indicator_; }
void FractionalCorrectedTrade::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator FractionalCorrectedTrade::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void FractionalCorrectedTrade::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

ShortSaleRestrictionIndicator FractionalCorrectedTrade::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void FractionalCorrectedTrade::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

std::size_t FractionalCorrectedTrade::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalCorrectedTrade", wire_size, length);

    offset += sale_conditions_.decode(data + offset, length - offset);

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    fractional_trade_volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    stop_stock_indicator_ = static_cast<StopStockIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_indicator_ = static_cast<TradeThroughExemptIndicator>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FractionalCorrectedTrade::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalCorrectedTrade", wire_size, capacity);

    offset += sale_conditions_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_trade_volume_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(stop_stock_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    return offset;
}

std::size_t FractionalCorrectedTrade::encoded_size() const {
    return wire_size;
}

void FractionalCorrectedTrade::print(std::ostream& out) const {
    out << "FractionalCorrectedTrade{";
    out << "sale_conditions=";
    sale_conditions_.print(out);
    out << ", trade_price=";
    out << trade_price_;
    out << ", fractional_trade_volume=";
    out << fractional_trade_volume_;
    out << ", sellers_sale_days=";
    out << static_cast<int>(sellers_sale_days_);
    out << ", stop_stock_indicator=";
    out << stop_stock_indicator_;
    out << ", trade_through_exempt_indicator=";
    out << trade_through_exempt_indicator_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << '}';
}

bool FractionalCorrectedTrade::operator==(const FractionalCorrectedTrade& other) const {
    return sale_conditions_ == other.sale_conditions_
        && trade_price_ == other.trade_price_
        && fractional_trade_volume_ == other.fractional_trade_volume_
        && sellers_sale_days_ == other.sellers_sale_days_
        && stop_stock_indicator_ == other.stop_stock_indicator_
        && trade_through_exempt_indicator_ == other.trade_through_exempt_indicator_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_;
}

bool FractionalCorrectedTrade::operator!=(const FractionalCorrectedTrade& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FractionalCorrectedTrade& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
