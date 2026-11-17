// Databento.MarketData.Normalized.Dbn.v1: messages/CbboMsg.hpp
#pragma once

#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Side.hpp"
#include "../bitfields/Flags.hpp"
#include "../types/SecondReserved1.hpp"
#include "../types/TsRecv.hpp"
#include "../types/Reserved8.hpp"
#include "../structs/ConsolidatedBidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

#pragma pack(push, 1)

// Subsampled consolidated market by price with a known book depth of 1; the record of the cbbo-1s and cbbo-1m schemas
struct CbboMsg {

    Price price;
    Size size;
    Reserved1 reserved_1;
    Side side;
    Flags flags;
    SecondReserved1 second_reserved_1;
    TsRecv ts_recv;
    Reserved8 reserved_8;
    ConsolidatedBidAskPair consolidated_bid_ask_pair;

    // parse method
    static CbboMsg* parse(std::byte* buffer) {
        return reinterpret_cast<CbboMsg*>(buffer);
    }

    // parse method const
    static const CbboMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const CbboMsg*>(buffer);
    }
};

#pragma pack(pop)
}
