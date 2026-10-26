#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/ImbalanceCondition.hpp"
#include "../types/MdEntrySizeQuantityOptional.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

#pragma pack(push, 1)

// Auction Imbalance 19 Message
struct auction_imbalance_19_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::md_update_action md_update_action;
        sbe_binaryumdf::imbalance_condition imbalance_condition;
        sbe_binaryumdf::md_entry_size_quantity_optional md_entry_size_quantity_optional;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static auction_imbalance_19_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_imbalance_19_message*>(buffer);
    }

    // parse method const
    static const auction_imbalance_19_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_imbalance_19_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_imbalance_19_message::fields_type, security_id) == 0, "unexpected offset of auction_imbalance_19_message::fields_type::security_id");
static_assert(offsetof(auction_imbalance_19_message::fields_type, match_event_indicator) == 8, "unexpected offset of auction_imbalance_19_message::fields_type::match_event_indicator");
static_assert(offsetof(auction_imbalance_19_message::fields_type, md_update_action) == 9, "unexpected offset of auction_imbalance_19_message::fields_type::md_update_action");
static_assert(offsetof(auction_imbalance_19_message::fields_type, imbalance_condition) == 10, "unexpected offset of auction_imbalance_19_message::fields_type::imbalance_condition");
static_assert(offsetof(auction_imbalance_19_message::fields_type, md_entry_size_quantity_optional) == 12, "unexpected offset of auction_imbalance_19_message::fields_type::md_entry_size_quantity_optional");
static_assert(offsetof(auction_imbalance_19_message::fields_type, md_entry_timestamp) == 20, "unexpected offset of auction_imbalance_19_message::fields_type::md_entry_timestamp");
static_assert(offsetof(auction_imbalance_19_message::fields_type, rpt_seq) == 28, "unexpected offset of auction_imbalance_19_message::fields_type::rpt_seq");
static_assert(sizeof(auction_imbalance_19_message::fields_type) == 32, "unexpected sizeof auction_imbalance_19_message::fields_type");
static_assert(sizeof(auction_imbalance_19_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 32, "unexpected sizeof auction_imbalance_19_message");

#pragma pack(pop)
}
