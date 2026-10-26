#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/OpenEligibilityStatus.hpp"
#include "../types/MinimumAllowablePrice.hpp"
#include "../types/MaximumAllowablePrice.hpp"
#include "../types/NearExecutionPrice.hpp"
#include "../types/NearExecutionTime.hpp"
#include "../types/LowerPriceRangeCollar.hpp"
#include "../types/UpperPriceRangeCollar.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// This message is disseminated only for Direct Listing with Capital Raise (DLCR) securities
struct DirectListingWithCapitalRaisePriceDiscoveryMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    OpenEligibilityStatus open_eligibility_status;
    MinimumAllowablePrice minimum_allowable_price;
    MaximumAllowablePrice maximum_allowable_price;
    NearExecutionPrice near_execution_price;
    NearExecutionTime near_execution_time;
    LowerPriceRangeCollar lower_price_range_collar;
    UpperPriceRangeCollar upper_price_range_collar;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static DirectListingWithCapitalRaisePriceDiscoveryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<DirectListingWithCapitalRaisePriceDiscoveryMessage*>(buffer);
    }

    // parse method const
    static const DirectListingWithCapitalRaisePriceDiscoveryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const DirectListingWithCapitalRaisePriceDiscoveryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const DirectListingWithCapitalRaisePriceDiscoveryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const DirectListingWithCapitalRaisePriceDiscoveryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
