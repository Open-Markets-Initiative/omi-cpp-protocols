#pragma once

#include "../types/Symbol.hpp"
#include "../types/StockGroup.hpp"
#include "../types/Cusip.hpp"
#include "../types/BoardLot.hpp"
#include "../types/Currency.hpp"
#include "../types/FaceValue.hpp"
#include "../types/LastSale.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

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
