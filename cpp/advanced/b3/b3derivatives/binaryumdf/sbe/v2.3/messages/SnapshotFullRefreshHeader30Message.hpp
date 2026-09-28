#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/TotNumBids.hpp"
#include "../types/TotNumOffers.hpp"
#include "../types/TotNumStats.hpp"
#include "../types/Offset26Padding2.hpp"
#include "../types/LastRptSeq.hpp"
#include "../types/LastSequenceVersion.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

// Snapshot Full Refresh Header 30 Message
struct snapshot_full_refresh_header_30_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::last_msg_seq_num_processed last_msg_seq_num_processed;
        sbe_binaryumdf::tot_num_reports tot_num_reports;
        sbe_binaryumdf::tot_num_bids tot_num_bids;
        sbe_binaryumdf::tot_num_offers tot_num_offers;
        sbe_binaryumdf::tot_num_stats tot_num_stats;
        sbe_binaryumdf::offset_26_padding_2 offset_26_padding_2;
        sbe_binaryumdf::last_rpt_seq last_rpt_seq;
        sbe_binaryumdf::last_sequence_version last_sequence_version;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static snapshot_full_refresh_header_30_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh_header_30_message*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh_header_30_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh_header_30_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, security_id) == 0, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::security_id");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, last_msg_seq_num_processed) == 8, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::last_msg_seq_num_processed");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, tot_num_reports) == 12, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::tot_num_reports");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, tot_num_bids) == 16, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::tot_num_bids");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, tot_num_offers) == 20, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::tot_num_offers");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, tot_num_stats) == 24, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::tot_num_stats");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, offset_26_padding_2) == 26, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::offset_26_padding_2");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, last_rpt_seq) == 28, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::last_rpt_seq");
static_assert(offsetof(snapshot_full_refresh_header_30_message::fields_type, last_sequence_version) == 32, "unexpected offset of snapshot_full_refresh_header_30_message::fields_type::last_sequence_version");
static_assert(sizeof(snapshot_full_refresh_header_30_message::fields_type) == 34, "unexpected sizeof snapshot_full_refresh_header_30_message::fields_type");
static_assert(sizeof(snapshot_full_refresh_header_30_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 34, "unexpected sizeof snapshot_full_refresh_header_30_message");

#pragma pack(pop)
}
