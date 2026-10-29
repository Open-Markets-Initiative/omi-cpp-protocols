#pragma once

#include "../structs/SaleConditions.hpp"
#include "../types/TradePriceLong.hpp"
#include "../types/TradeVolumeLong.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct OriginalTrade {

    SaleConditions sale_conditions;
    TradePriceLong trade_price_long;
    TradeVolumeLong trade_volume_long;
    SellersSaleDays sellers_sale_days;
    StopStockIndicator stop_stock_indicator;
    TradeThroughExemptIndicator trade_through_exempt_indicator;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PriorDayTradeDateAndTime prior_day_trade_date_and_time;

    // parse method
    static OriginalTrade* parse(std::byte* buffer) {
        return reinterpret_cast<OriginalTrade*>(buffer);
    }

    // parse method const
    static const OriginalTrade* parse(const std::byte* buffer) {
        return reinterpret_cast<const OriginalTrade*>(buffer);
    }
};

#pragma pack(pop)
}
