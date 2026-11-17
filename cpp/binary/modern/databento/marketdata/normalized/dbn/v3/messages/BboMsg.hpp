// Databento.MarketData.Normalized.Dbn.v3: messages/BboMsg.hpp
#pragma once

#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Side.hpp"
#include "../bitfields/Flags.hpp"
#include "../types/SecondReserved1.hpp"
#include "../types/TsRecv.hpp"
#include "../types/Reserved4.hpp"
#include "../types/Sequence.hpp"
#include "../structs/BidAskPair.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

#pragma pack(push, 1)

// Subsampled market by price with a known book depth of 1; the record of the bbo-1s and bbo-1m schemas
struct BboMsg {

    Price price;
    Size size;
    Reserved1 reserved_1;
    Side side;
    Flags flags;
    SecondReserved1 second_reserved_1;
    TsRecv ts_recv;
    Reserved4 reserved_4;
    Sequence sequence;
    BidAskPair bid_ask_pair;

    // parse method
    static BboMsg* parse(std::byte* buffer) {
        return reinterpret_cast<BboMsg*>(buffer);
    }

    // parse method const
    static const BboMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const BboMsg*>(buffer);
    }
};

#pragma pack(pop)
}
