#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TradeDate.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TradeId.hpp"
#include "../types/CorrectionNumber.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// used to publish cancellation of a Simple Instrument trade which was previously published via an Order Execution Message
struct TradeCancelMessage {

    Timestamp timestamp;
    TradeDate trade_date;
    InstrumentId instrument_id;
    TradeId trade_id;
    CorrectionNumber correction_number;
    Price price;
    Size size;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 14;

    // parse method
    static TradeCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCancelMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const TradeCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
