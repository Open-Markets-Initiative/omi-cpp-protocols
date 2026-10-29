#pragma once

#include <cstddef>
#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/FractionalTradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

struct fractional_original_trade {

    cta_output::sale_conditions sale_conditions;
    cta_output::trade_price trade_price;
    cta_output::fractional_trade_volume fractional_trade_volume;
    cta_output::sellers_sale_days sellers_sale_days;
    cta_output::stop_stock_indicator stop_stock_indicator;
    cta_output::trade_through_exempt_indicator trade_through_exempt_indicator;
    cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;

    // parse method
    static fractional_original_trade* parse(std::byte* buffer) {
        return reinterpret_cast<fractional_original_trade*>(buffer);
    }

    // parse method const
    static const fractional_original_trade* parse(const std::byte* buffer) {
        return reinterpret_cast<const fractional_original_trade*>(buffer);
    }
};

// layout verification
static_assert(offsetof(fractional_original_trade, sale_conditions) == 0, "unexpected offset of fractional_original_trade::sale_conditions");
static_assert(offsetof(fractional_original_trade, trade_price) == 4, "unexpected offset of fractional_original_trade::trade_price");
static_assert(offsetof(fractional_original_trade, fractional_trade_volume) == 12, "unexpected offset of fractional_original_trade::fractional_trade_volume");
static_assert(offsetof(fractional_original_trade, sellers_sale_days) == 20, "unexpected offset of fractional_original_trade::sellers_sale_days");
static_assert(offsetof(fractional_original_trade, stop_stock_indicator) == 21, "unexpected offset of fractional_original_trade::stop_stock_indicator");
static_assert(offsetof(fractional_original_trade, trade_through_exempt_indicator) == 22, "unexpected offset of fractional_original_trade::trade_through_exempt_indicator");
static_assert(offsetof(fractional_original_trade, short_sale_restriction_indicator) == 23, "unexpected offset of fractional_original_trade::short_sale_restriction_indicator");
static_assert(sizeof(fractional_original_trade) == 24, "unexpected sizeof fractional_original_trade");

#pragma pack(pop)
}
