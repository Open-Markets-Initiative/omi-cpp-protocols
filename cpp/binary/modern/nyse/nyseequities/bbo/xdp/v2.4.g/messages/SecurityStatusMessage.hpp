#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved4.hpp"
#include "../types/Price1.hpp"
#include "../types/Price2.hpp"
#include "../types/SsrTriggeringExchangeId.hpp"
#include "../types/SsrTriggeringVolume.hpp"
#include "../types/Time.hpp"
#include "../types/SsrState.hpp"
#include "../types/MarketState.hpp"
#include "../types/SessionState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

#pragma pack(push, 1)

// This message informs clients of changes in the status of a specific security, such as Trading Halts, Short Sale Restriction state changes, etc.
struct SecurityStatusMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    SecurityStatus security_status;
    HaltCondition halt_condition;
    Reserved4 reserved_4;
    Price1 price_1;
    Price2 price_2;
    SsrTriggeringExchangeId ssr_triggering_exchange_id;
    SsrTriggeringVolume ssr_triggering_volume;
    Time time;
    SsrState ssr_state;
    MarketState market_state;
    SessionState session_state;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 34;

    // parse method
    static SecurityStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatusMessage*>(buffer);
    }

    // parse method const
    static const SecurityStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
