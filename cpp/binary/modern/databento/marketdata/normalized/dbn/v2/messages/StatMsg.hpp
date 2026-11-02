#pragma once

#include "../types/TsRecv.hpp"
#include "../types/TsRef.hpp"
#include "../types/Price.hpp"
#include "../types/Quantity.hpp"
#include "../types/Sequence.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/StatType.hpp"
#include "../types/Channel.hpp"
#include "../types/UpdateAction.hpp"
#include "../types/StatFlags.hpp"
#include "../types/Reserved6.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// A statistics message; the record of the statistics schema
struct StatMsg {

    TsRecv ts_recv;
    TsRef ts_ref;
    Price price;
    Quantity quantity;
    Sequence sequence;
    TsInDelta ts_in_delta;
    StatType stat_type;
    Channel channel;
    UpdateAction update_action;
    StatFlags stat_flags;
    Reserved6 reserved_6;

    // parse method
    static StatMsg* parse(std::byte* buffer) {
        return reinterpret_cast<StatMsg*>(buffer);
    }

    // parse method const
    static const StatMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const StatMsg*>(buffer);
    }
};

#pragma pack(pop)
}
