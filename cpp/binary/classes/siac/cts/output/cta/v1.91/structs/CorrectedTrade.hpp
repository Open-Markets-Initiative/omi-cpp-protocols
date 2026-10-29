#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/StopStockIndicator.hpp"
#include "../enums/TradeThroughExemptIndicator.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"
#include "../structs/SaleConditions.hpp"

namespace siac::cts::output::cta::v1_91 {

// Corrected Trade
class CorrectedTrade {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 28;

    CorrectedTrade() = default;
    CorrectedTrade(const SaleConditions& sale_conditions, Decimal trade_price_long, std::uint32_t trade_volume_long, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator, const PriorDayTradeDateAndTime& prior_day_trade_date_and_time);

    // Sale Conditions: Sale Conditions
    const SaleConditions& sale_conditions() const;
    SaleConditions& sale_conditions();
    void set_sale_conditions(const SaleConditions& value);

    // Trade Price Long: The Trade Price is the monetary value of an individual share of
    // security at the time of the trade
    Decimal trade_price_long() const;
    void set_trade_price_long(Decimal value);

    // Trade Volume Long: Trade volume of the original transaction
    std::uint32_t trade_volume_long() const;
    void set_trade_volume_long(std::uint32_t value);

    // Sellers Sale Days: Specifies the number of days that may elapse before delivery of the
    // security
    std::uint8_t sellers_sale_days() const;
    void set_sellers_sale_days(std::uint8_t value);

    // Stop Stock Indicator: The transaction that constituted the trade-through was the
    // execution by a trading center of an order for which, at the time of receipt of the
    // order, the trading center had guaranteed an execution at no worse than a specified price
    StopStockIndicator stop_stock_indicator() const;
    void set_stop_stock_indicator(StopStockIndicator value);

    // Trade Through Exempt Indicator: Denotes whether or not a trade is exempt (Rule 611) and
    // when used jointly with certain Sale Conditions, will more fully describe the
    // characteristics of a particular trade
    TradeThroughExemptIndicator trade_through_exempt_indicator() const;
    void set_trade_through_exempt_indicator(TradeThroughExemptIndicator value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect for a security
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Prior Day Trade Date And Time: Prior Day Trade Date and Time
    const PriorDayTradeDateAndTime& prior_day_trade_date_and_time() const;
    PriorDayTradeDateAndTime& prior_day_trade_date_and_time();
    void set_prior_day_trade_date_and_time(const PriorDayTradeDateAndTime& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CorrectedTrade& other) const;
    bool operator!=(const CorrectedTrade& other) const;

  private:
    SaleConditions sale_conditions_{};
    Decimal trade_price_long_{ 0, -6 };
    std::uint32_t trade_volume_long_{};
    std::uint8_t sellers_sale_days_{};
    StopStockIndicator stop_stock_indicator_{};
    TradeThroughExemptIndicator trade_through_exempt_indicator_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PriorDayTradeDateAndTime prior_day_trade_date_and_time_{};
};

std::ostream& operator<<(std::ostream& out, const CorrectedTrade& value);

} // namespace siac::cts::output::cta::v1_91
