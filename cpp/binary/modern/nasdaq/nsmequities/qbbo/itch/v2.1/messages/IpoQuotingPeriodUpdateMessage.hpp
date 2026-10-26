#pragma once

#include "../types/Tracking.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/IpoQuotationReleaseTime.hpp"
#include "../types/IpoQuotationReleaseQualifier.hpp"
#include "../types/IpoPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// Indicates the anticipated IPO quotation release time of a security.
struct IpoQuotingPeriodUpdateMessage {

    Tracking tracking;
    TimeStamp time_stamp;
    Stock stock;
    IpoQuotationReleaseTime ipo_quotation_release_time;
    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier;
    IpoPrice ipo_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'K';

    // parse method
    static IpoQuotingPeriodUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<IpoQuotingPeriodUpdateMessage*>(buffer);
    }

    // parse method const
    static const IpoQuotingPeriodUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const IpoQuotingPeriodUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const IpoQuotingPeriodUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const IpoQuotingPeriodUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
