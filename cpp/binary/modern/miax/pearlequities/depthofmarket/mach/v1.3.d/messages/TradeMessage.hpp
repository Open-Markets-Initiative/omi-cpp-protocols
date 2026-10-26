#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/TradeId.hpp"
#include "../types/CorrectionNumber.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../bitfields/TradeFlags.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This message format is used to publish trade executions for orders not displayed on the book. Executions for orders routed and executed in another trading center and trade corrections are also published using this message.
struct TradeMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    TradeId trade_id;
    CorrectionNumber correction_number;
    Price price;
    Size size;
    TradeFlags trade_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 10;

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
