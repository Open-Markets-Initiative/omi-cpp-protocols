#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/NewOrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"
#include "../types/CustIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Published when a cancel/replace order is received. The resting order is replaced with a new order containing the same outright or complex series, side and attribution, a new Order ID, and the price and size specified.
struct OptionsReplaceOrderMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OrderId order_id;
    NewOrderId new_order_id;
    Price price;
    Volume volume;
    Side side;
    Reserved1 reserved_1;
    CustIndicator cust_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 304;

    // parse method
    static OptionsReplaceOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsReplaceOrderMessage*>(buffer);
    }

    // parse method const
    static const OptionsReplaceOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsReplaceOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsReplaceOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsReplaceOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
