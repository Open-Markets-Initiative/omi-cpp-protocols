#include "CorrectedTrade.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v1_91 {

CorrectedTrade::CorrectedTrade(const SaleConditions& sale_conditions, Decimal trade_price_long, std::uint32_t trade_volume_long, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator, const PriorDayTradeDateAndTime& prior_day_trade_date_and_time)
  : sale_conditions_(sale_conditions), trade_price_long_(trade_price_long), trade_volume_long_(trade_volume_long), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), short_sale_restriction_indicator_(short_sale_restriction_indicator), prior_day_trade_date_and_time_(prior_day_trade_date_and_time) {}

const SaleConditions& CorrectedTrade::sale_conditions() const { return sale_conditions_; }
SaleConditions& CorrectedTrade::sale_conditions() { return sale_conditions_; }
void CorrectedTrade::set_sale_conditions(const SaleConditions& value) { sale_conditions_ = value; }

Decimal CorrectedTrade::trade_price_long() const { return trade_price_long_; }
void CorrectedTrade::set_trade_price_long(Decimal value) { trade_price_long_ = value; }

std::uint32_t CorrectedTrade::trade_volume_long() const { return trade_volume_long_; }
void CorrectedTrade::set_trade_volume_long(std::uint32_t value) { trade_volume_long_ = value; }

std::uint8_t CorrectedTrade::sellers_sale_days() const { return sellers_sale_days_; }
void CorrectedTrade::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator CorrectedTrade::stop_stock_indicator() const { return stop_stock_indicator_; }
void CorrectedTrade::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator CorrectedTrade::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void CorrectedTrade::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

ShortSaleRestrictionIndicator CorrectedTrade::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void CorrectedTrade::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

const PriorDayTradeDateAndTime& CorrectedTrade::prior_day_trade_date_and_time() const { return prior_day_trade_date_and_time_; }
PriorDayTradeDateAndTime& CorrectedTrade::prior_day_trade_date_and_time() { return prior_day_trade_date_and_time_; }
void CorrectedTrade::set_prior_day_trade_date_and_time(const PriorDayTradeDateAndTime& value) { prior_day_trade_date_and_time_ = value; }

std::size_t CorrectedTrade::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CorrectedTrade", wire_size, length);

    offset += sale_conditions_.decode(data + offset, length - offset);

    trade_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    trade_volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    stop_stock_indicator_ = static_cast<StopStockIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_indicator_ = static_cast<TradeThroughExemptIndicator>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    offset += prior_day_trade_date_and_time_.decode(data + offset, length - offset);

    return offset;
}

std::size_t CorrectedTrade::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CorrectedTrade", wire_size, capacity);

    offset += sale_conditions_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_long_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_long_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(stop_stock_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    offset += prior_day_trade_date_and_time_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t CorrectedTrade::encoded_size() const {
    return wire_size;
}

void CorrectedTrade::print(std::ostream& out) const {
    out << "CorrectedTrade{";
    out << "sale_conditions=";
    sale_conditions_.print(out);
    out << ", trade_price_long=";
    out << trade_price_long_;
    out << ", trade_volume_long=";
    out << trade_volume_long_;
    out << ", sellers_sale_days=";
    out << static_cast<int>(sellers_sale_days_);
    out << ", stop_stock_indicator=";
    out << stop_stock_indicator_;
    out << ", trade_through_exempt_indicator=";
    out << trade_through_exempt_indicator_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", prior_day_trade_date_and_time=";
    prior_day_trade_date_and_time_.print(out);
    out << '}';
}

bool CorrectedTrade::operator==(const CorrectedTrade& other) const {
    return sale_conditions_ == other.sale_conditions_
        && trade_price_long_ == other.trade_price_long_
        && trade_volume_long_ == other.trade_volume_long_
        && sellers_sale_days_ == other.sellers_sale_days_
        && stop_stock_indicator_ == other.stop_stock_indicator_
        && trade_through_exempt_indicator_ == other.trade_through_exempt_indicator_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && prior_day_trade_date_and_time_ == other.prior_day_trade_date_and_time_;
}

bool CorrectedTrade::operator!=(const CorrectedTrade& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CorrectedTrade& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
