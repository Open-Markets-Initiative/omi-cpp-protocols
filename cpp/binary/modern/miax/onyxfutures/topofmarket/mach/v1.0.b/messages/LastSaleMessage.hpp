#pragma once

#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// used to disseminate trades that are resulting from executions on MIAX Futures Onyx during the current trading session
struct LastSaleMessage {

    Timestamp timestamp;
    InstrumentId instrument_id;
    TradeId trade_id;
    Price price;
    Size size;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 16;

    // parse method
    static LastSaleMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LastSaleMessage*>(buffer);
    }

    // parse method const
    static const LastSaleMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LastSaleMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LastSaleMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const LastSaleMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
