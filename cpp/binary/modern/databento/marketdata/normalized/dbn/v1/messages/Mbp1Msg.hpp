// Databento.MarketData.Normalized.Dbn.v1: messages/Mbp1Msg.hpp
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
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

// Market by price implementation with a known book depth of 1; the record of the mbp-1 and tbbo schemas
struct Mbp1Msg {

    Price price;
    Size size;
    Action action;
    Side side;
    Flags flags;
    Depth depth;
    TsRecv ts_recv;
    TsInDelta ts_in_delta;
    Sequence sequence;
    BidAskPair bid_ask_pair;

    // parse method
    static Mbp1Msg* parse(std::byte* buffer) {
        return reinterpret_cast<Mbp1Msg*>(buffer);
    }

    // parse method const
    static const Mbp1Msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const Mbp1Msg*>(buffer);
    }
};

#pragma pack(pop)
}
