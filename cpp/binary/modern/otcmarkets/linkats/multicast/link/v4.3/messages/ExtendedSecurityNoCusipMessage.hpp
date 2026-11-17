// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/ExtendedSecurityNoCusipMessage.hpp
#pragma once

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
#include "../bitfields/SecurityFlags.hpp"
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
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// Extended Security message without CUSIP information. This message may be sent at system startup or intraday following a technical outage.
struct ExtendedSecurityNoCusipMessage {

    ChannelSeqNum channel_seq_num;
    Symbol symbol;
    LastUpdateMilli last_update_milli;
    SecurityAction security_action;
    OtcIssuerId otc_issuer_id;
    SecurityDesc security_desc;
    ShortName short_name;
    AssetClass asset_class;
    SecurityType security_type;
    PrimaryMarket primary_market;
    SecurityId security_id;
    SecurityFlags security_flags;
    Tier tier;
    ReportingStatus reporting_status;
    DisclosureStatus disclosure_status;
    SecurityStatus security_status;
    ParValue par_value;
    Coupon coupon;
    MaturityDateMilli maturity_date_milli;
    CallableDateMilli callable_date_milli;
    AdrRatio adr_ratio;
    AdrLevel adr_level;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 16;

    // parse method
    static ExtendedSecurityNoCusipMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExtendedSecurityNoCusipMessage*>(buffer);
    }

    // parse method const
    static const ExtendedSecurityNoCusipMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExtendedSecurityNoCusipMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ExtendedSecurityNoCusipMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ExtendedSecurityNoCusipMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
