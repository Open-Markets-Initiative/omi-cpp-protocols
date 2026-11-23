// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MocImbalanceMessage.hpp
#pragma once

#include "../types/Symbol.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ImbalanceVolume.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ImbalanceReferencePrice.hpp"
#include "../types/PairedVolume.hpp"
#include "../types/MarketOrderImbalanceVolume.hpp"
#include "../types/MarketOrderImbalanceSide.hpp"
#include "../types/NearIndicativeClosingPrice.hpp"
#include "../types/FarIndicativeClosingPrice.hpp"
#include "../types/PriceVariation.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

// 
struct MocImbalanceMessage {

    Symbol symbol;
    ImbalanceSide imbalance_side;
    ImbalanceVolume imbalance_volume;
    TradingSystemTimeStamp trading_system_time_stamp;
    ImbalanceReferencePrice imbalance_reference_price;
    PairedVolume paired_volume;
    MarketOrderImbalanceVolume market_order_imbalance_volume;
    MarketOrderImbalanceSide market_order_imbalance_side;
    NearIndicativeClosingPrice near_indicative_closing_price;
    FarIndicativeClosingPrice far_indicative_closing_price;
    PriceVariation price_variation;

    // parse method
    static MocImbalanceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MocImbalanceMessage*>(buffer);
    }

    // parse method const
    static const MocImbalanceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MocImbalanceMessage*>(buffer);
    }
};

#pragma pack(pop)
}
