#pragma once

#include "../types/Symbol.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ImbalanceVolume.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ImbalanceReferencePrice.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct MocImbalanceMessage {

    Symbol symbol;
    ImbalanceSide imbalance_side;
    ImbalanceVolume imbalance_volume;
    TradingSystemTimeStamp trading_system_time_stamp;
    ImbalanceReferencePrice imbalance_reference_price;

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
