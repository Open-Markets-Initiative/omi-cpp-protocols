// Databento.MarketData.Normalized.Dbn.v2: messages/OhlcvMsg.hpp
#pragma once

#include "../types/Open.hpp"
#include "../types/High.hpp"
#include "../types/Low.hpp"
#include "../types/Close.hpp"
#include "../types/Volume.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// Open, high, low, close, and volume; the record of the ohlcv schemas
struct OhlcvMsg {

    Open open;
    High high;
    Low low;
    Close close;
    Volume volume;

    // parse method
    static OhlcvMsg* parse(std::byte* buffer) {
        return reinterpret_cast<OhlcvMsg*>(buffer);
    }

    // parse method const
    static const OhlcvMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const OhlcvMsg*>(buffer);
    }
};

#pragma pack(pop)
}
