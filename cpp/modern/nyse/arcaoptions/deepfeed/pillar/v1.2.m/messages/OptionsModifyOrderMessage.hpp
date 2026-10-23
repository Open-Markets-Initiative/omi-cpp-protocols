#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PositionChange.hpp"
#include "../types/Side.hpp"
#include "../types/CustIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Sent when the price or volume of an order is changed due to an event other than a cancel-replace, or full or partial execution.
struct OptionsModifyOrderMessage {

    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OrderId order_id;
    Price price;
    Volume volume;
    PositionChange position_change;
    Side side;
    CustIndicator cust_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 301;

    // parse method
    static OptionsModifyOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsModifyOrderMessage*>(buffer);
    }

    // parse method const
    static const OptionsModifyOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsModifyOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsModifyOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsModifyOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
