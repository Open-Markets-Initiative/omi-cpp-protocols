// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/SecurityMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/Symbol.hpp"
#include "../types/LastUpdateMilli.hpp"
#include "../types/SecurityAction.hpp"
#include "../types/AssetClass.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityFlags.hpp"
#include "../types/Tier.hpp"
#include "../types/ReportingStatus.hpp"
#include "../types/SecurityStatus.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Security Message
struct security_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::symbol symbol;
        link_multicast::last_update_milli last_update_milli;
        link_multicast::security_action security_action;
        link_multicast::asset_class asset_class;
        link_multicast::security_id security_id;
        link_multicast::security_flags security_flags;
        link_multicast::tier tier;
        link_multicast::reporting_status reporting_status;
        link_multicast::security_status security_status;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::security_message};

    fields_type fields;

    // parse method
    static security_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_message*>(buffer);
    }

    // parse method const
    static const security_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_message::fields_type, channel_seq_num) == 0, "unexpected offset of security_message::fields_type::channel_seq_num");
static_assert(offsetof(security_message::fields_type, symbol) == 4, "unexpected offset of security_message::fields_type::symbol");
static_assert(offsetof(security_message::fields_type, last_update_milli) == 14, "unexpected offset of security_message::fields_type::last_update_milli");
static_assert(offsetof(security_message::fields_type, security_action) == 22, "unexpected offset of security_message::fields_type::security_action");
static_assert(offsetof(security_message::fields_type, asset_class) == 23, "unexpected offset of security_message::fields_type::asset_class");
static_assert(offsetof(security_message::fields_type, security_id) == 24, "unexpected offset of security_message::fields_type::security_id");
static_assert(offsetof(security_message::fields_type, security_flags) == 28, "unexpected offset of security_message::fields_type::security_flags");
static_assert(offsetof(security_message::fields_type, tier) == 29, "unexpected offset of security_message::fields_type::tier");
static_assert(offsetof(security_message::fields_type, reporting_status) == 30, "unexpected offset of security_message::fields_type::reporting_status");
static_assert(offsetof(security_message::fields_type, security_status) == 31, "unexpected offset of security_message::fields_type::security_status");
static_assert(sizeof(security_message::fields_type) == 32, "unexpected sizeof security_message::fields_type");
static_assert(sizeof(security_message) == sizeof(link_multicast::message_header) + 32, "unexpected sizeof security_message");

#pragma pack(pop)
}
