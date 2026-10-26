#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

// Low Price 25 Message
struct low_price_25_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::md_update_action md_update_action;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::md_future_price md_future_price;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static low_price_25_message* parse(std::byte* buffer) {
        return reinterpret_cast<low_price_25_message*>(buffer);
    }

    // parse method const
    static const low_price_25_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const low_price_25_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(low_price_25_message::fields_type, security_id) == 0, "unexpected offset of low_price_25_message::fields_type::security_id");
static_assert(offsetof(low_price_25_message::fields_type, match_event_indicator) == 8, "unexpected offset of low_price_25_message::fields_type::match_event_indicator");
static_assert(offsetof(low_price_25_message::fields_type, md_update_action) == 9, "unexpected offset of low_price_25_message::fields_type::md_update_action");
static_assert(offsetof(low_price_25_message::fields_type, trade_date) == 10, "unexpected offset of low_price_25_message::fields_type::trade_date");
static_assert(offsetof(low_price_25_message::fields_type, md_future_price) == 12, "unexpected offset of low_price_25_message::fields_type::md_future_price");
static_assert(offsetof(low_price_25_message::fields_type, md_entry_timestamp) == 20, "unexpected offset of low_price_25_message::fields_type::md_entry_timestamp");
static_assert(offsetof(low_price_25_message::fields_type, rpt_seq) == 28, "unexpected offset of low_price_25_message::fields_type::rpt_seq");
static_assert(sizeof(low_price_25_message::fields_type) == 32, "unexpected sizeof low_price_25_message::fields_type");
static_assert(sizeof(low_price_25_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 32, "unexpected sizeof low_price_25_message");

#pragma pack(pop)
}
