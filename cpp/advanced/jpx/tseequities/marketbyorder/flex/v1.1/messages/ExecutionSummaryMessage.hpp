#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeMicroseconds.hpp"
#include "../types/TriggeredSide.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/TotalInvalidation.hpp"
#include "../types/LastPrice.hpp"
#include "../types/MatchId.hpp"
#include "../types/BestOffer.hpp"
#include "../types/BestBid.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Execution Summary Message
struct execution_summary_message {

    struct fields_type {
        flex_marketbyorder::time_microseconds time_microseconds;
        flex_marketbyorder::triggered_side triggered_side;
        flex_marketbyorder::total_volume total_volume;
        flex_marketbyorder::total_invalidation total_invalidation;
        flex_marketbyorder::last_price last_price;
        flex_marketbyorder::match_id match_id;
        flex_marketbyorder::best_offer best_offer;
        flex_marketbyorder::best_bid best_bid;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::execution_summary_message};

    fields_type fields;

    // parse method
    static execution_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_summary_message*>(buffer);
    }

    // parse method const
    static const execution_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_summary_message::fields_type, time_microseconds) == 0, "unexpected offset of execution_summary_message::fields_type::time_microseconds");
static_assert(offsetof(execution_summary_message::fields_type, triggered_side) == 4, "unexpected offset of execution_summary_message::fields_type::triggered_side");
static_assert(offsetof(execution_summary_message::fields_type, total_volume) == 5, "unexpected offset of execution_summary_message::fields_type::total_volume");
static_assert(offsetof(execution_summary_message::fields_type, total_invalidation) == 11, "unexpected offset of execution_summary_message::fields_type::total_invalidation");
static_assert(offsetof(execution_summary_message::fields_type, last_price) == 17, "unexpected offset of execution_summary_message::fields_type::last_price");
static_assert(offsetof(execution_summary_message::fields_type, match_id) == 25, "unexpected offset of execution_summary_message::fields_type::match_id");
static_assert(offsetof(execution_summary_message::fields_type, best_offer) == 29, "unexpected offset of execution_summary_message::fields_type::best_offer");
static_assert(offsetof(execution_summary_message::fields_type, best_bid) == 37, "unexpected offset of execution_summary_message::fields_type::best_bid");
static_assert(sizeof(execution_summary_message::fields_type) == 45, "unexpected sizeof execution_summary_message::fields_type");
static_assert(sizeof(execution_summary_message) == sizeof(message_header) + 45, "unexpected sizeof execution_summary_message");

#pragma pack(pop)
}
