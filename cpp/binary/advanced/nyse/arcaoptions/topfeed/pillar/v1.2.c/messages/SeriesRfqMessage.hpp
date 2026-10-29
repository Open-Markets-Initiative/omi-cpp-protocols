#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
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

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Series Rfq Message
struct series_rfq_message {

    struct fields_type {
        pillar_topfeed::source_time source_time;
        pillar_topfeed::source_time_ns source_time_ns;
        pillar_topfeed::series_index series_index;
        pillar_topfeed::series_seq_num series_seq_num;
        pillar_topfeed::side side;
        pillar_topfeed::type type;
        pillar_topfeed::capacity capacity;
        pillar_topfeed::total_quantity total_quantity;
        pillar_topfeed::working_price working_price;
        pillar_topfeed::participant participant;
        pillar_topfeed::auction_id auction_id;
        pillar_topfeed::rfq_status rfq_status;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::series_rfq_message};

    fields_type fields;

    // parse method
    static series_rfq_message* parse(std::byte* buffer) {
        return reinterpret_cast<series_rfq_message*>(buffer);
    }

    // parse method const
    static const series_rfq_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const series_rfq_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(series_rfq_message::fields_type, source_time) == 0, "unexpected offset of series_rfq_message::fields_type::source_time");
static_assert(offsetof(series_rfq_message::fields_type, source_time_ns) == 4, "unexpected offset of series_rfq_message::fields_type::source_time_ns");
static_assert(offsetof(series_rfq_message::fields_type, series_index) == 8, "unexpected offset of series_rfq_message::fields_type::series_index");
static_assert(offsetof(series_rfq_message::fields_type, series_seq_num) == 12, "unexpected offset of series_rfq_message::fields_type::series_seq_num");
static_assert(offsetof(series_rfq_message::fields_type, side) == 16, "unexpected offset of series_rfq_message::fields_type::side");
static_assert(offsetof(series_rfq_message::fields_type, type) == 17, "unexpected offset of series_rfq_message::fields_type::type");
static_assert(offsetof(series_rfq_message::fields_type, capacity) == 18, "unexpected offset of series_rfq_message::fields_type::capacity");
static_assert(offsetof(series_rfq_message::fields_type, total_quantity) == 19, "unexpected offset of series_rfq_message::fields_type::total_quantity");
static_assert(offsetof(series_rfq_message::fields_type, working_price) == 23, "unexpected offset of series_rfq_message::fields_type::working_price");
static_assert(offsetof(series_rfq_message::fields_type, participant) == 27, "unexpected offset of series_rfq_message::fields_type::participant");
static_assert(offsetof(series_rfq_message::fields_type, auction_id) == 31, "unexpected offset of series_rfq_message::fields_type::auction_id");
static_assert(offsetof(series_rfq_message::fields_type, rfq_status) == 39, "unexpected offset of series_rfq_message::fields_type::rfq_status");
static_assert(sizeof(series_rfq_message::fields_type) == 40, "unexpected sizeof series_rfq_message::fields_type");
static_assert(sizeof(series_rfq_message) == sizeof(pillar_topfeed::message_header) + 40, "unexpected sizeof series_rfq_message");

#pragma pack(pop)
}
