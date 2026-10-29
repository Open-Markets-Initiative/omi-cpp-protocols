#pragma once

#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/FractionalTradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../structs/PriorDayTradeDateAndTime.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct FractionalPriorDayOriginalTrade {

    SaleConditions sale_conditions;
    TradePrice trade_price;
    FractionalTradeVolume fractional_trade_volume;
    SellersSaleDays sellers_sale_days;
    StopStockIndicator stop_stock_indicator;
    TradeThroughExemptIndicator trade_through_exempt_indicator;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PriorDayTradeDateAndTime prior_day_trade_date_and_time;

    // parse method
    static FractionalPriorDayOriginalTrade* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalPriorDayOriginalTrade*>(buffer);
    }

    // parse method const
    static const FractionalPriorDayOriginalTrade* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalPriorDayOriginalTrade*>(buffer);
    }
};

#pragma pack(pop)
}
