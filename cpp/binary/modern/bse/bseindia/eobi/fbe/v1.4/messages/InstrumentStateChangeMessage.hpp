#pragma once

#include "../types/SecurityId.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad5.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Provides state information for a single instrument.
struct InstrumentStateChangeMessage {

    SecurityId security_id;
    SecurityStatus security_status;
    SecurityTradingStatus security_trading_status;
    FastMarketIndicator fast_market_indicator;
    Pad5 pad_5;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13301;

    // parse method
    static InstrumentStateChangeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentStateChangeMessage*>(buffer);
    }

    // parse method const
    static const InstrumentStateChangeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentStateChangeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentStateChangeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InstrumentStateChangeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
