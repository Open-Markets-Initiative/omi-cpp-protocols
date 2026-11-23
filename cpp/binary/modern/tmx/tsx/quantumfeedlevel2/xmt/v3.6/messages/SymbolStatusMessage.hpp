// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/SymbolStatusMessage.hpp
#pragma once

#include "../types/Symbol.hpp"
#include "../types/StockGroup.hpp"
#include "../types/Cusip.hpp"
#include "../types/BoardLot.hpp"
#include "../types/Currency.hpp"
#include "../types/FaceValue.hpp"
#include "../types/LastSale.hpp"
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"
#include "../types/BuyMaximumQuantity.hpp"
#include "../types/BuyMinimumQuantity.hpp"
#include "../types/SellMaximumQuantity.hpp"
#include "../types/SellMinimumQuantity.hpp"
#include "../types/StockState.hpp"
#include "../types/TestSymbol.hpp"
#include "../types/MocEligible.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

// 
struct SymbolStatusMessage {

    Symbol symbol;
    StockGroup stock_group;
    Cusip cusip;
    BoardLot board_lot;
    Currency currency;
    FaceValue face_value;
    LastSale last_sale;
    ListingMarket listing_market;
    ProductType product_type;
    BuyMaximumQuantity buy_maximum_quantity;
    BuyMinimumQuantity buy_minimum_quantity;
    SellMaximumQuantity sell_maximum_quantity;
    SellMinimumQuantity sell_minimum_quantity;
    StockState stock_state;
    TestSymbol test_symbol;
    MocEligible moc_eligible;

    // parse method
    static SymbolStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolStatusMessage*>(buffer);
    }

    // parse method const
    static const SymbolStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
