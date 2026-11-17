// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/ExtendedSecurityNoCusipMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/Symbol.hpp"
#include "../types/LastUpdateMilli.hpp"
#include "../types/SecurityAction.hpp"
#include "../types/OtcIssuerId.hpp"
#include "../types/SecurityDesc.hpp"
#include "../types/ShortName.hpp"
#include "../types/AssetClass.hpp"
#include "../types/SecurityType.hpp"
#include "../types/PrimaryMarket.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityFlags.hpp"
#include "../types/Tier.hpp"
#include "../types/ReportingStatus.hpp"
#include "../types/DisclosureStatus.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/ParValue.hpp"
#include "../types/Coupon.hpp"
#include "../types/MaturityDateMilli.hpp"
#include "../types/CallableDateMilli.hpp"
#include "../types/AdrRatio.hpp"
#include "../types/AdrLevel.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;


#pragma pack(push, 1)

// Extended Security No Cusip Message
struct extended_security_no_cusip_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::symbol symbol;
        link_multicast::last_update_milli last_update_milli;
        link_multicast::security_action security_action;
        link_multicast::otc_issuer_id otc_issuer_id;
        link_multicast::security_desc security_desc;
        link_multicast::short_name short_name;
        link_multicast::asset_class asset_class;
        link_multicast::security_type security_type;
        link_multicast::primary_market primary_market;
        link_multicast::security_id security_id;
        link_multicast::security_flags security_flags;
        link_multicast::tier tier;
        link_multicast::reporting_status reporting_status;
        link_multicast::disclosure_status disclosure_status;
        link_multicast::security_status security_status;
        link_multicast::par_value par_value;
        link_multicast::coupon coupon;
        link_multicast::maturity_date_milli maturity_date_milli;
        link_multicast::callable_date_milli callable_date_milli;
        link_multicast::adr_ratio adr_ratio;
        link_multicast::adr_level adr_level;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::extended_security_no_cusip_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(link_multicast::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(link_multicast::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(link_multicast::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_var_data<std::uint8_t> security_detail() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data<std::uint8_t> issuer(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static extended_security_no_cusip_message* parse(std::byte* buffer) {
        return reinterpret_cast<extended_security_no_cusip_message*>(buffer);
    }

    // parse method const
    static const extended_security_no_cusip_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const extended_security_no_cusip_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(extended_security_no_cusip_message::fields_type, channel_seq_num) == 0, "unexpected offset of extended_security_no_cusip_message::fields_type::channel_seq_num");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, symbol) == 4, "unexpected offset of extended_security_no_cusip_message::fields_type::symbol");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, last_update_milli) == 14, "unexpected offset of extended_security_no_cusip_message::fields_type::last_update_milli");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, security_action) == 22, "unexpected offset of extended_security_no_cusip_message::fields_type::security_action");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, otc_issuer_id) == 23, "unexpected offset of extended_security_no_cusip_message::fields_type::otc_issuer_id");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, security_desc) == 27, "unexpected offset of extended_security_no_cusip_message::fields_type::security_desc");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, short_name) == 52, "unexpected offset of extended_security_no_cusip_message::fields_type::short_name");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, asset_class) == 77, "unexpected offset of extended_security_no_cusip_message::fields_type::asset_class");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, security_type) == 78, "unexpected offset of extended_security_no_cusip_message::fields_type::security_type");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, primary_market) == 83, "unexpected offset of extended_security_no_cusip_message::fields_type::primary_market");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, security_id) == 86, "unexpected offset of extended_security_no_cusip_message::fields_type::security_id");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, security_flags) == 90, "unexpected offset of extended_security_no_cusip_message::fields_type::security_flags");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, tier) == 91, "unexpected offset of extended_security_no_cusip_message::fields_type::tier");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, reporting_status) == 92, "unexpected offset of extended_security_no_cusip_message::fields_type::reporting_status");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, disclosure_status) == 93, "unexpected offset of extended_security_no_cusip_message::fields_type::disclosure_status");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, security_status) == 94, "unexpected offset of extended_security_no_cusip_message::fields_type::security_status");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, par_value) == 95, "unexpected offset of extended_security_no_cusip_message::fields_type::par_value");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, coupon) == 103, "unexpected offset of extended_security_no_cusip_message::fields_type::coupon");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, maturity_date_milli) == 111, "unexpected offset of extended_security_no_cusip_message::fields_type::maturity_date_milli");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, callable_date_milli) == 119, "unexpected offset of extended_security_no_cusip_message::fields_type::callable_date_milli");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, adr_ratio) == 127, "unexpected offset of extended_security_no_cusip_message::fields_type::adr_ratio");
static_assert(offsetof(extended_security_no_cusip_message::fields_type, adr_level) == 135, "unexpected offset of extended_security_no_cusip_message::fields_type::adr_level");
static_assert(sizeof(extended_security_no_cusip_message::fields_type) == 150, "unexpected sizeof extended_security_no_cusip_message::fields_type");

#pragma pack(pop)
}

#include "details/ExtendedSecurityNoCusipMessageWriter.hpp"
#include "details/ExtendedSecurityNoCusipMessageReader.hpp"
