#pragma once

#include <cstddef>
#include "../structs/SaleConditions.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/SellersSaleDays.hpp"
#include "../types/StopStockIndicator.hpp"
#include "../types/TradeThroughExemptIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

struct original_trade {

    cta_output::sale_conditions sale_conditions;
    cta_output::trade_price trade_price;
    cta_output::trade_volume trade_volume;
    cta_output::sellers_sale_days sellers_sale_days;
    cta_output::stop_stock_indicator stop_stock_indicator;
    cta_output::trade_through_exempt_indicator trade_through_exempt_indicator;
    cta_output::short_sale_restriction_indicator short_sale_restriction_indicator;

    // parse method
    static original_trade* parse(std::byte* buffer) {
        return reinterpret_cast<original_trade*>(buffer);
    }

    // parse method const
    static const original_trade* parse(const std::byte* buffer) {
        return reinterpret_cast<const original_trade*>(buffer);
    }
};

// layout verification
static_assert(offsetof(original_trade, sale_conditions) == 0, "unexpected offset of original_trade::sale_conditions");
static_assert(offsetof(original_trade, trade_price) == 4, "unexpected offset of original_trade::trade_price");
static_assert(offsetof(original_trade, trade_volume) == 12, "unexpected offset of original_trade::trade_volume");
static_assert(offsetof(original_trade, sellers_sale_days) == 16, "unexpected offset of original_trade::sellers_sale_days");
static_assert(offsetof(original_trade, stop_stock_indicator) == 17, "unexpected offset of original_trade::stop_stock_indicator");
static_assert(offsetof(original_trade, trade_through_exempt_indicator) == 18, "unexpected offset of original_trade::trade_through_exempt_indicator");
static_assert(offsetof(original_trade, short_sale_restriction_indicator) == 19, "unexpected offset of original_trade::short_sale_restriction_indicator");
static_assert(sizeof(original_trade) == 20, "unexpected sizeof original_trade");

#pragma pack(pop)
}
