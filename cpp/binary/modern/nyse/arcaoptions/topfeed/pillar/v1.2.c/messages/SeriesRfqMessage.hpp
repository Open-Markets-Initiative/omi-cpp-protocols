#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/Side.hpp"
#include "../types/Type.hpp"
#include "../types/Capacity.hpp"
#include "../types/TotalQuantity.hpp"
#include "../types/WorkingPrice.hpp"
#include "../types/Participant.hpp"
#include "../types/AuctionId.hpp"
#include "../types/RfqStatus.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// The Request for Series RFQ message is published for outright series.
struct SeriesRfqMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    Side side;
    Type type;
    Capacity capacity;
    TotalQuantity total_quantity;
    WorkingPrice working_price;
    Participant participant;
    AuctionId auction_id;
    RfqStatus rfq_status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 307;

    // parse method
    static SeriesRfqMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SeriesRfqMessage*>(buffer);
    }

    // parse method const
    static const SeriesRfqMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SeriesRfqMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SeriesRfqMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SeriesRfqMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
