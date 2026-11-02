#pragma once

#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/Action.hpp"
#include "../types/Side.hpp"
#include "../bitfields/Flags.hpp"
#include "../types/Depth.hpp"
#include "../types/TsRecv.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/Sequence.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// Market by price implementation with a book depth of 0; equivalent to MBP-0, the record of the trades schema
struct TradeMsg {

    Price price;
    Size size;
    Action action;
    Side side;
    Flags flags;
    Depth depth;
    TsRecv ts_recv;
    TsInDelta ts_in_delta;
    Sequence sequence;

    // parse method
    static TradeMsg* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMsg*>(buffer);
    }

    // parse method const
    static const TradeMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMsg*>(buffer);
    }
};

#pragma pack(pop)
}
