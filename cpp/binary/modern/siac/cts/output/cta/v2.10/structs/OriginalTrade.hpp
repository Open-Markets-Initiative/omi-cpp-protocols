#pragma once

#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct OriginalTrade {

    SaleConditions sale_conditions;
    TradePrice trade_price;
    TradeVolume trade_volume;
    SellersSaleDays sellers_sale_days;
    StopStockIndicator stop_stock_indicator;
    TradeThroughExemptIndicator trade_through_exempt_indicator;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;

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
