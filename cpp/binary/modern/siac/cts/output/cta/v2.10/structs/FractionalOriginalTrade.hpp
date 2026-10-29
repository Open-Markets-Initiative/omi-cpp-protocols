#pragma once

#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/FractionalTradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct FractionalOriginalTrade {

    SaleConditions sale_conditions;
    TradePrice trade_price;
    FractionalTradeVolume fractional_trade_volume;
    SellersSaleDays sellers_sale_days;
    StopStockIndicator stop_stock_indicator;
    TradeThroughExemptIndicator trade_through_exempt_indicator;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;

    // parse method
    static FractionalOriginalTrade* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalOriginalTrade*>(buffer);
    }

    // parse method const
    static const FractionalOriginalTrade* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalOriginalTrade*>(buffer);
    }
};

#pragma pack(pop)
}
