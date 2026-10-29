#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/Size.hpp"
#include "../types/Volume.hpp"
#include "../types/High.hpp"
#include "../types/Low.hpp"
#include "../types/First.hpp"
#include "../types/TradeCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

#pragma pack(push, 1)

// The ticker message is used to send real time trade information
struct ComplexStrategyTickerMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    LastPrice last_price;
    Size size;
    Volume volume;
    High high;
    Low low;
    First first;
    TradeCondition trade_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 't';

    // parse method
    static ComplexStrategyTickerMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexStrategyTickerMessage*>(buffer);
    }

    // parse method const
    static const ComplexStrategyTickerMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexStrategyTickerMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexStrategyTickerMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexStrategyTickerMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
