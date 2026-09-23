#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCode.hpp"
#include "../types/OperationalHaltAction.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// An Operational Halt means that there has been an interruption of service on the identified security impacting only the designated Market Center
struct OperationalHaltMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    MarketCode market_code;
    OperationalHaltAction operational_halt_action;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'h';

    // parse method
    static OperationalHaltMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OperationalHaltMessage*>(buffer);
    }

    // parse method const
    static const OperationalHaltMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OperationalHaltMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OperationalHaltMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OperationalHaltMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
