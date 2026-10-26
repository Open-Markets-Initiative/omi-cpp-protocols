#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/Side.hpp"
#include "../types/FirmId.hpp"
#include "../types/Reserved1.hpp"
#include "../types/CustIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Sent as part of a refresh response for every order currently resting on the book.
struct OptionsAddOrderRefreshMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    OrderId order_id;
    Price price;
    Volume volume;
    Side side;
    FirmId firm_id;
    Reserved1 reserved_1;
    CustIndicator cust_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 306;

    // parse method
    static OptionsAddOrderRefreshMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsAddOrderRefreshMessage*>(buffer);
    }

    // parse method const
    static const OptionsAddOrderRefreshMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsAddOrderRefreshMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsAddOrderRefreshMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsAddOrderRefreshMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
