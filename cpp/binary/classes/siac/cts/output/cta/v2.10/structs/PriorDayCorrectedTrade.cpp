#include "PriorDayCorrectedTrade.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

PriorDayCorrectedTrade::PriorDayCorrectedTrade(const SaleConditions& sale_conditions, Decimal trade_price, std::uint32_t trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator, const PriorDayTradeDateAndTime& prior_day_trade_date_and_time)
  : sale_conditions_(sale_conditions), trade_price_(trade_price), trade_volume_(trade_volume), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), short_sale_restriction_indicator_(short_sale_restriction_indicator), prior_day_trade_date_and_time_(prior_day_trade_date_and_time) {}

const SaleConditions& PriorDayCorrectedTrade::sale_conditions() const { return sale_conditions_; }
SaleConditions& PriorDayCorrectedTrade::sale_conditions() { return sale_conditions_; }
void PriorDayCorrectedTrade::set_sale_conditions(const SaleConditions& value) { sale_conditions_ = value; }

Decimal PriorDayCorrectedTrade::trade_price() const { return trade_price_; }
void PriorDayCorrectedTrade::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t PriorDayCorrectedTrade::trade_volume() const { return trade_volume_; }
void PriorDayCorrectedTrade::set_trade_volume(std::uint32_t value) { trade_volume_ = value; }

std::uint8_t PriorDayCorrectedTrade::sellers_sale_days() const { return sellers_sale_days_; }
void PriorDayCorrectedTrade::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator PriorDayCorrectedTrade::stop_stock_indicator() const { return stop_stock_indicator_; }
void PriorDayCorrectedTrade::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator PriorDayCorrectedTrade::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void PriorDayCorrectedTrade::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

ShortSaleRestrictionIndicator PriorDayCorrectedTrade::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void PriorDayCorrectedTrade::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

const PriorDayTradeDateAndTime& PriorDayCorrectedTrade::prior_day_trade_date_and_time() const { return prior_day_trade_date_and_time_; }
PriorDayTradeDateAndTime& PriorDayCorrectedTrade::prior_day_trade_date_and_time() { return prior_day_trade_date_and_time_; }
void PriorDayCorrectedTrade::set_prior_day_trade_date_and_time(const PriorDayTradeDateAndTime& value) { prior_day_trade_date_and_time_ = value; }

std::size_t PriorDayCorrectedTrade::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriorDayCorrectedTrade", wire_size, length);

    offset += sale_conditions_.decode(data + offset, length - offset);

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    trade_volume_ = wire::read_u32_be(data + offset);
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

std::size_t PriorDayCorrectedTrade::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriorDayCorrectedTrade", wire_size, capacity);

    offset += sale_conditions_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_));
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

std::size_t PriorDayCorrectedTrade::encoded_size() const {
    return wire_size;
}

void PriorDayCorrectedTrade::print(std::ostream& out) const {
    out << "PriorDayCorrectedTrade{";
    out << "sale_conditions=";
    sale_conditions_.print(out);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_volume=";
    out << trade_volume_;
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

bool PriorDayCorrectedTrade::operator==(const PriorDayCorrectedTrade& other) const {
    return sale_conditions_ == other.sale_conditions_
        && trade_price_ == other.trade_price_
        && trade_volume_ == other.trade_volume_
        && sellers_sale_days_ == other.sellers_sale_days_
        && stop_stock_indicator_ == other.stop_stock_indicator_
        && trade_through_exempt_indicator_ == other.trade_through_exempt_indicator_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && prior_day_trade_date_and_time_ == other.prior_day_trade_date_and_time_;
}

bool PriorDayCorrectedTrade::operator!=(const PriorDayCorrectedTrade& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PriorDayCorrectedTrade& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
