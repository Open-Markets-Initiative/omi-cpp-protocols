#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradingSession.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

#pragma pack(push, 1)

// This message announces the start of a new trading session for a specified symbol.
struct TradingSessionChangeMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    TradingSession trading_session;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 33;

    // parse method
    static TradingSessionChangeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingSessionChangeMessage*>(buffer);
    }

    // parse method const
    static const TradingSessionChangeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingSessionChangeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingSessionChangeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradingSessionChangeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
