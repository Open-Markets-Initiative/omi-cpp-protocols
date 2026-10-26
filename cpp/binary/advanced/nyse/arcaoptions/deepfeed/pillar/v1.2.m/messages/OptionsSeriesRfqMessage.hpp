#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/RfqSide.hpp"
#include "../types/Type.hpp"
#include "../types/Capacity.hpp"
#include "../types/TotalQuantity.hpp"
#include "../types/WorkingPrice.hpp"
#include "../types/Participant.hpp"
#include "../types/AuctionId.hpp"
#include "../types/RfqStatus.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Series Rfq Message
struct options_series_rfq_message {

    struct fields_type {
        pillar_deepfeed::source_time source_time;
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::rfq_side rfq_side;
        pillar_deepfeed::type type;
        pillar_deepfeed::capacity capacity;
        pillar_deepfeed::total_quantity total_quantity;
        pillar_deepfeed::working_price working_price;
        pillar_deepfeed::participant participant;
        pillar_deepfeed::auction_id auction_id;
        pillar_deepfeed::rfq_status rfq_status;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_series_rfq_message};

    fields_type fields;

    // parse method
    static options_series_rfq_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_series_rfq_message*>(buffer);
    }

    // parse method const
    static const options_series_rfq_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_series_rfq_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_series_rfq_message::fields_type, source_time) == 0, "unexpected offset of options_series_rfq_message::fields_type::source_time");
static_assert(offsetof(options_series_rfq_message::fields_type, source_time_ns) == 4, "unexpected offset of options_series_rfq_message::fields_type::source_time_ns");
static_assert(offsetof(options_series_rfq_message::fields_type, series_index) == 8, "unexpected offset of options_series_rfq_message::fields_type::series_index");
static_assert(offsetof(options_series_rfq_message::fields_type, series_seq_num) == 12, "unexpected offset of options_series_rfq_message::fields_type::series_seq_num");
static_assert(offsetof(options_series_rfq_message::fields_type, rfq_side) == 16, "unexpected offset of options_series_rfq_message::fields_type::rfq_side");
static_assert(offsetof(options_series_rfq_message::fields_type, type) == 17, "unexpected offset of options_series_rfq_message::fields_type::type");
static_assert(offsetof(options_series_rfq_message::fields_type, capacity) == 18, "unexpected offset of options_series_rfq_message::fields_type::capacity");
static_assert(offsetof(options_series_rfq_message::fields_type, total_quantity) == 19, "unexpected offset of options_series_rfq_message::fields_type::total_quantity");
static_assert(offsetof(options_series_rfq_message::fields_type, working_price) == 23, "unexpected offset of options_series_rfq_message::fields_type::working_price");
static_assert(offsetof(options_series_rfq_message::fields_type, participant) == 27, "unexpected offset of options_series_rfq_message::fields_type::participant");
static_assert(offsetof(options_series_rfq_message::fields_type, auction_id) == 31, "unexpected offset of options_series_rfq_message::fields_type::auction_id");
static_assert(offsetof(options_series_rfq_message::fields_type, rfq_status) == 39, "unexpected offset of options_series_rfq_message::fields_type::rfq_status");
static_assert(sizeof(options_series_rfq_message::fields_type) == 40, "unexpected sizeof options_series_rfq_message::fields_type");
static_assert(sizeof(options_series_rfq_message) == sizeof(pillar_deepfeed::message_header) + 40, "unexpected sizeof options_series_rfq_message");

#pragma pack(pop)
}
