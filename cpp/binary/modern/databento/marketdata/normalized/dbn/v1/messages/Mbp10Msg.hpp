// Databento.MarketData.Normalized.Dbn.v1: messages/Mbp10Msg.hpp
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

// Market by price implementation with a known book depth of 10
struct Mbp10Msg {

    Price price;
    Size size;
    Action action;
    Side side;
    Flags flags;
    Depth depth;
    TsRecv ts_recv;
    TsInDelta ts_in_delta;
    Sequence sequence;
    BidAskPair bid_ask_pair[10];

    // parse method
    static Mbp10Msg* parse(std::byte* buffer) {
        return reinterpret_cast<Mbp10Msg*>(buffer);
    }

    // parse method const
    static const Mbp10Msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const Mbp10Msg*>(buffer);
    }
};

#pragma pack(pop)
}
