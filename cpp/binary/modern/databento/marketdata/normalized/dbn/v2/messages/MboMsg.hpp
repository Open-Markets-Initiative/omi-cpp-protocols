#pragma once

#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../bitfields/Flags.hpp"
#include "../types/ChannelId.hpp"
#include "../types/Action.hpp"
#include "../types/Side.hpp"
#include "../types/TsRecv.hpp"
#include "../types/TsInDelta.hpp"
#include "../types/Sequence.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// A market-by-order (MBO) tick message
struct MboMsg {

    OrderId order_id;
    Price price;
    Size size;
    Flags flags;
    ChannelId channel_id;
    Action action;
    Side side;
    TsRecv ts_recv;
    TsInDelta ts_in_delta;
    Sequence sequence;

    // parse method
    static MboMsg* parse(std::byte* buffer) {
        return reinterpret_cast<MboMsg*>(buffer);
    }

    // parse method const
    static const MboMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const MboMsg*>(buffer);
    }
};

#pragma pack(pop)
}
