#pragma once

#include <cstddef>
#include "../structs/SaleConditions.hpp"
#include "../types/TradePriceLong.hpp"
#include "../types/TradeVolumeLong.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v1_91 {

namespace cta_output = ::siac::cts::output::cta::v1_91;

#pragma pack(push, 1)

struct corrected_trade {

    cta_output::sale_conditions sale_conditions;
    cta_output::trade_price_long trade_price_long;
    cta_output::trade_volume_long trade_volume_long;
    cta_output::sellers_sale_days sellers_sale_days;
    cta_output::stop_stock_indicator stop_stock_indicator;
    cta_output::trade_through_exempt_indicator trade_through_exempt_indicator;
    cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;
    cta_output::prior_day_trade_date_and_time prior_day_trade_date_and_time;

    // parse method
    static corrected_trade* parse(std::byte* buffer) {
        return reinterpret_cast<corrected_trade*>(buffer);
    }

    // parse method const
    static const corrected_trade* parse(const std::byte* buffer) {
        return reinterpret_cast<const corrected_trade*>(buffer);
    }
};

// layout verification
static_assert(offsetof(corrected_trade, sale_conditions) == 0, "unexpected offset of corrected_trade::sale_conditions");
static_assert(offsetof(corrected_trade, trade_price_long) == 4, "unexpected offset of corrected_trade::trade_price_long");
static_assert(offsetof(corrected_trade, trade_volume_long) == 12, "unexpected offset of corrected_trade::trade_volume_long");
static_assert(offsetof(corrected_trade, sellers_sale_days) == 16, "unexpected offset of corrected_trade::sellers_sale_days");
static_assert(offsetof(corrected_trade, stop_stock_indicator) == 17, "unexpected offset of corrected_trade::stop_stock_indicator");
static_assert(offsetof(corrected_trade, trade_through_exempt_indicator) == 18, "unexpected offset of corrected_trade::trade_through_exempt_indicator");
static_assert(offsetof(corrected_trade, short_sale_restriction_indicator) == 19, "unexpected offset of corrected_trade::short_sale_restriction_indicator");
static_assert(offsetof(corrected_trade, prior_day_trade_date_and_time) == 20, "unexpected offset of corrected_trade::prior_day_trade_date_and_time");
static_assert(sizeof(corrected_trade) == 28, "unexpected sizeof corrected_trade");

#pragma pack(pop)
}
