#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/IpoQuotationReleaseTime.hpp"
#include "../types/IpoQuotationReleaseQualifier.hpp"
#include "../types/IpoPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Indicates the anticipated IPO quotation release time of a security.
struct IpoQuotingPeriodUpdate {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    IpoQuotationReleaseTime ipo_quotation_release_time;
    IpoQuotationReleaseQualifier ipo_quotation_release_qualifier;
    IpoPrice ipo_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'K';

    // parse method
    static IpoQuotingPeriodUpdate* parse(std::byte* buffer) {
        return reinterpret_cast<IpoQuotingPeriodUpdate*>(buffer);
    }

    // parse method const
    static const IpoQuotingPeriodUpdate* parse(const std::byte* buffer) {
        return reinterpret_cast<const IpoQuotingPeriodUpdate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const IpoQuotingPeriodUpdate* parse(const MessageHeader* header) {
        return reinterpret_cast<const IpoQuotingPeriodUpdate*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
