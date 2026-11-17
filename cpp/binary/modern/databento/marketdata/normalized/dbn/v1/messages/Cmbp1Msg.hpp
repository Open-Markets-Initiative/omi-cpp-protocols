// Databento.MarketData.Normalized.Dbn.v1: messages/Cmbp1Msg.hpp
#pragma once

#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/Action.hpp"
#include "../types/Side.hpp"
#include "../bitfields/Flags.hpp"
#include "../types/Reserved1.hpp"
#include "../types/TsRecv.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/Reserved4.hpp"
#include "../structs/ConsolidatedBidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

// Consolidated market by price implementation with a known book depth of 1; the record of the cmbp-1 and tcbbo schemas
struct Cmbp1Msg {

    Price price;
    Size size;
    Action action;
    Side side;
    Flags flags;
    Reserved1 reserved_1;
    TsRecv ts_recv;
    TsInDelta ts_in_delta;
    Reserved4 reserved_4;
    ConsolidatedBidAskPair consolidated_bid_ask_pair;

    // parse method
    static Cmbp1Msg* parse(std::byte* buffer) {
        return reinterpret_cast<Cmbp1Msg*>(buffer);
    }

    // parse method const
    static const Cmbp1Msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const Cmbp1Msg*>(buffer);
    }
};

#pragma pack(pop)
}
